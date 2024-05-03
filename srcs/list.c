/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:33:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/03 13:30:11 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void _add_element_sorted(t_list **list, struct Entry *content, int (*compare)(const struct Entry *, const struct Entry *))
{
	t_list *new_node = ft_lstnew(content);

	if (*list == NULL || compare(content, (*list)->content) < 0)
	{
		new_node->next = *list;
		*list = new_node;
	}
	else
	{
		t_list *current = *list;
		while (current->next != NULL && compare(content, current->next->content) > 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}

void	add_element(t_list **list, struct Entry *content)
{
	if (state.sort_type == sort_none)
		ft_lstadd_back(list, ft_lstnew(content));
	else if (state.sort_type == sort_by_time)
		_add_element_sorted(list, content, compare_entries_by_time);
	else if (state.sort_type == sort_by_size)
		_add_element_sorted(list, content, compare_entries_by_size);
	else if (state.sort_type == sort_by_name)
		_add_element_sorted(list, content, compare_entries_by_name);
}

void reverse_list(t_list **list)
{
	t_list *prev = NULL;
	t_list *current = *list;
	t_list *next = NULL;

	while (current != NULL)
	{
		next = current->next; // Store next node
		current->next = prev; // Reverse current node's pointer
		prev = current;		  // Move pointers one position ahead
		current = next;
	}
	*list = prev; // Adjust the head pointer to point to the new first node
}

void	list_contents(t_list *list)
{
	t_list *file = list;

	while (file)
	{
		struct Entry *_entry = (struct Entry *)file->content;

		if (S_ISDIR(_entry->statbuf.st_mode))
			print_dir(file);
		else
			entry_print(_entry);
		file = file->next;
		if (state.add_newline == false && file)
			state.add_newline = true;
	}
}

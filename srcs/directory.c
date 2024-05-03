/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:56:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/03 17:48:41 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory.h"

#define CREATE_PATH(name_, s1_, s2_)                     \
	size_t len_ = (ft_strlen(s1_) + ft_strlen(s2_)) + 2; \
	char name_[len_];                                    \
	ft_memset(name_, 0, len_);                           \
	ft_strcat(ft_strcat(ft_strcpy(name_, s1_), "/"), s2_);

static t_list *get_dir_entries(const char *path, long *total_blocks)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*list;

	if (!path)
		return (NULL);
	if ((dir = opendir(path)) == NULL)
	{
		show_errno_error(path);
		return (NULL);
	}

	list = NULL;
	if (total_blocks)
		*total_blocks = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (SHOULD_SKIP_HIDDEN(entry->d_name))
			continue;

		CREATE_PATH(full_path, path, entry->d_name);
		struct Entry *new_entry = entry_create(entry->d_name, full_path);
		if (new_entry)
		{
			add_element(&list, new_entry);
			if ((state.options & OPTION_LONG || state.options & OPTION_PRINT_SIZE) && total_blocks)
				*total_blocks += new_entry->statbuf.st_blocks;
		}
	}
	closedir(dir);
	if (state.options & OPTION_REVERSE)
		reverse_list(&list);
	return (list);
}

void print_dir(t_list *file)
{
	long		total_blocks;
	t_list		*entries_start;
	t_list		*entries;
	t_list		*dirs;
	const char	*dirname = ((struct Entry *)file->content)->name;

	ft_memset(&state.width, 0, sizeof(state.width));
	entries_start = entries = get_dir_entries(dirname, &total_blocks);
	dirs = NULL;

	if (!entries)
		return ;
	if (state.add_newline)
		ft_putchar('\n');
	if (state.show_dir_names && entries)
		ft_printf("%s:\n", (char *)dirname);
	if (state.options & OPTION_LONG || state.options & OPTION_PRINT_SIZE)
		ft_printf("total %ld\n", total_blocks / 2);
	
	while (entries)
	{
		struct Entry *current_entry = (struct Entry *)entries->content;

		if (!current_entry || SHOULD_SKIP_HIDDEN(current_entry->name))
		{
			entries = entries->next;
			continue;
		}
		if (state.options & OPTION_RECURSIVE && ft_strcmp(current_entry->name, ".") != 0 && ft_strcmp(current_entry->name, "..") != 0 && S_ISDIR(current_entry->statbuf.st_mode))
		{
			CREATE_PATH(join, dirname, current_entry->name);
			struct Entry *new_entry = entry_create(join, NULL);
			if (new_entry)
			{
				new_entry->statbuf = current_entry->statbuf;
				add_element(&dirs, new_entry);
			}
		}
		entry_print(current_entry);
		entries = entries->next;
	}
	ft_lstclear(&entries_start, entry_destroy);
	if (dirs)
	{
		if (state.options & OPTION_REVERSE)
			reverse_list(&dirs);
		state.add_newline = true;
		list_contents(dirs);
		ft_lstclear(&dirs, entry_destroy);
	}
}

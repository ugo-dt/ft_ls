/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:56:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/16 21:05:39 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory.h"

static t_list *get_dir_entries(const char *path, long *total_blocks)
{
	DIR *dir;
	struct dirent *entry;
	t_list *list = NULL;

	if ((dir = opendir(path)) == NULL)
	{
		show_errno_error(path);
		return (NULL);
	}

	if (total_blocks)
		*total_blocks = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (SHOULD_SKIP_HIDDEN(entry->d_name))
			continue;

		char	*full_path = ft_strjoin_3(path, "/", entry->d_name);
		if (!full_path)
		{
			ft_dprintf(STDERR_FILENO, "\nout of memory\n");
			exit(EXIT_FAILURE);
		}

		struct Entry *_new_entry = entry_create(ft_strdup(entry->d_name), full_path);
		if (!_new_entry)
			continue;

		add_element(&list, _new_entry);

		if (state.options & OPTION_LONG || state.options & OPTION_PRINT_SIZE)
		{
			if (total_blocks)
				*total_blocks += _new_entry->statbuf.st_blocks;
		}
	}
	closedir(dir);

	if (state.options & OPTION_REVERSE)
		reverse_list(&list);
	return (list);
}

void print_dir(t_list *file, int *add_newline)
{
	t_list	*entries_start;
	t_list	*entries;
	t_list	*dirs;
	long	total_blocks;
	const char *dirname = ((struct Entry *)file->content)->name;

	ft_memset(&state.width, 0, sizeof(state.width));
	entries_start = entries = get_dir_entries(dirname, &total_blocks);
	dirs = NULL;

	if (!entries)
		return ;
	if (*add_newline)
		ft_putchar('\n');
	if (state.show_dir_names && entries)
		ft_printf("%s:\n", (char *)dirname);
	if (state.options & OPTION_LONG || state.options & OPTION_PRINT_SIZE)
		ft_printf("total %ld\n", total_blocks / 2);
	while (entries)
	{
		struct Entry *_entry = (struct Entry *)entries->content;

		if (SHOULD_SKIP_HIDDEN(_entry->name))
		{
			entries = entries->next;
			continue;
		}
		if (state.options & OPTION_RECURSIVE && ft_strcmp(_entry->name, ".") != 0 && ft_strcmp(_entry->name, "..") != 0 && S_ISDIR(_entry->statbuf.st_mode))
		{
			struct Entry *_new_entry = entry_create(ft_strjoin_3(dirname, "/", _entry->name), NULL);
			if (_new_entry)
			{
				_new_entry->statbuf = _entry->statbuf;
				add_element(&dirs, _new_entry);
			}
		}
		entry_print(_entry);
		entries = entries->next;
	}
	ft_lstclear(&entries_start, (LstIterFunction)entry_destroy);
	if (dirs)
	{
		if (state.options & OPTION_REVERSE)
			reverse_list(&dirs);
		*add_newline = 1;
		list_contents(dirs, add_newline);
		ft_lstclear(&dirs, (LstIterFunction)entry_destroy);
	}
}

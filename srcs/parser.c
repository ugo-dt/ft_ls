/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:20:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/16 21:03:53 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

# define _REMOVE_OPTION(_option) (state.options &= ~(_option))

# define MATCH_OPTION(_option_string, _option_code, ...) \
	if (ft_strcmp(argv[i], _option_string) == 0) \
	{ \
		state.options |= _option_code; \
		__VA_ARGS__; \
		continue; \
	} \

static int	parse_options(int argc, char **argv)
{
	int	i;

	for (i = 1; i < argc; i++)
	{
		if (!argv[i] || argv[i][0] != '-')
			continue;
		if (ft_strncmp(argv[i], "--", 2) == 0)
		{
			if (ft_strlen(argv[i]) > 2)
			{
				MATCH_OPTION("--all", OPTION_ALL, _REMOVE_OPTION(OPTION_ALMOST_ALL));
				MATCH_OPTION("--almost-all", OPTION_ALMOST_ALL, _REMOVE_OPTION(OPTION_ALL));
				MATCH_OPTION("--reverse", OPTION_REVERSE);
				MATCH_OPTION("--recursive", OPTION_RECURSIVE);
				MATCH_OPTION("--format=long", OPTION_LONG);
				MATCH_OPTION("--format=verbose", OPTION_LONG);
				MATCH_OPTION("--size", OPTION_PRINT_SIZE);
				ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": unrecognized option '%s'\n", argv[i]);
				return (-1);
			}
		}
		else
		{
			for (int j = 1; argv[i][j] != '\0'; j++)
			{
				switch (argv[i][j])
				{
				case 'a':
					state.options |= OPTION_ALL;
					state.options &= ~OPTION_ALMOST_ALL;
					break;
				case 'A':
					state.options |= OPTION_ALMOST_ALL;
					state.options &= ~OPTION_ALL;
					break;
				case 'f':
					state.options |= OPTION_ALL;
					state.sort_type = sort_none;
					break;
				case 'g':
					state.options |= (OPTION_DONT_SHOW_OWNER | OPTION_LONG);
					break;
				case 'l':
					state.options |= OPTION_LONG;
					break;
				case 'o':
					state.options |= (OPTION_DONT_SHOW_GROUP | OPTION_LONG);
					break;
				case 'r':
					state.options |= OPTION_REVERSE;
					break;
				case 'R':
					state.options |= OPTION_RECURSIVE;
					break;
				case 's':
					state.options |= OPTION_PRINT_SIZE;
					break;
				case 'S':
					state.sort_type = sort_by_size;
					break;
				case 't':
					state.sort_type = sort_by_time;
					break;
				case 'U':
					state.sort_type = sort_none;
					break;
				default:
					ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": invalid option -- '%c'\n", argv[i][j]);
					return (-1);
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	parse_arguments(int argc, char **argv, t_list **files, t_list **dirs)
{
	int	filec = 0;

	if (parse_options(argc, argv) != 0)
		exit(EXIT_INVALID_OPTION);
	for (int i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-' && ft_strlen(argv[i]) > 1))
			continue;

		char *name = ft_strdup(argv[i]);
		char *full_path = ft_strdup(argv[i]);

		struct Entry *_new_entry = entry_create(name, full_path);
		if (!_new_entry)
		{
			state.exit_value = EXIT_FAILURE;
			free(name);
			free(full_path);
			continue;
		}
		if (is_entry_directory(_new_entry))
			add_element(dirs, _new_entry);
		else
			add_element(files, _new_entry);
		filec++;
	}
	int dircount = ft_lstsize(*dirs);
	int filecount = ft_lstsize(*files);

	// default path
	if (dircount == 0 && filecount == 0 && !filec)
	{
		struct Entry *_new_entry = xmalloc(sizeof(*_new_entry));
		_new_entry->name = ft_strdup(".");

		if (do_stat(".", &_new_entry->statbuf) != 0)
			show_errno_error(_new_entry->name);
		else
			add_element(dirs, _new_entry);
	}

	if (dircount > 1 || filecount > 1 || (dircount >= 1 && filecount >= 1) || (state.options & OPTION_RECURSIVE) || (filec > 2))
		state.show_dir_names = true;
	if (state.options & OPTION_REVERSE)
	{
		reverse_list(files);
		reverse_list(dirs);
	}
	return (0);
}

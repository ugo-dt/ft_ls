/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:20:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/03 18:19:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

# define IS_SORT(_option_code) (_option_code == OPTION_SORT_BY_SIZE || _option_code == OPTION_SORT_BY_TIME || _option_code == OPTION_SORT_NONE)

#define MATCH_FORMAT(_name, _code, _word)                  \
	do                                                     \
	{                                                      \
		if (ft_strncmp(word, _word, ft_strlen(word)) == 0) \
		{                                                  \
			if (IS_SORT(_code))                            \
				state.sort_type = (enum sort_type)_code;   \
			else                                           \
				state.options |= _code;                    \
			state.options |= _code;                        \
			return (0);                                    \
		}                                                  \
	} while (0);

static inline int match_word(char *word, char *option)
{
	if (!word || !word[0])
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": option '%s' requires an argument\n", option);
		return (-1);
	}
	if (ft_strcmp(option, "--format") == 0)
	{
		FORMATS_ITER(MATCH_FORMAT);
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": invalid argument '%s' for '%s'\nValid arguments are:\n  - 'verbose', 'long'\n", word, option);
	}
	else if (ft_strcmp(option, "--sort") == 0)
	{
		SORTS_ITER(MATCH_FORMAT);
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": invalid argument '%s' for '%s'\nValid arguments are:\n  - 'none'\n  - 'time'\n  - 'size'\n", word, option);
	}
	return (-1);
}

#define MATCH_LONG_OPTION(_name, _code, _short, _long, _removes, ...)                        \
	do                                                                                       \
	{                                                                                        \
		char *_eq = ft_strchr(argv[i], '=');                                                 \
		if ((_code == OPTION_FORMAT && (_eq && ft_strncmp(argv[i], "--format", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], _long, len) == 0) \
			|| (_code == OPTION_SORT && (_eq && ft_strncmp(argv[i], "--sort", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], _long, len) == 0)\
			) \
		{                                                                                    \
			char *_word;                                                                     \
			if (!_eq)                                                                        \
			{                                                                                \
				i++;                                                                         \
				_word = argv[i];                                                             \
			}                                                                                \
			else                                                                             \
			{                                                                                \
				len--;                                                                       \
				_word = _eq + 1;                                                             \
			}                                                                                \
			if (match_word(_word, _long) == 0)                                               \
			{                                                                                \
				current |= _code;                                                            \
				count++;                                                                     \
			}                                                                                \
			else                                                                             \
				return (-1);                                                                 \
		}                                                                                    \
		else if (ft_strncmp(argv[i], _long, len) == 0)                                       \
		{                                                                                    \
			count++;                                                                         \
			current |= _code;                                                                \
			if (_removes)                                                                    \
				state.options &= ~(_removes);                                                \
		}                                                                                    \
	} while (0);

#define PRINT_AMBIGUOUS(_name, _code, _short, _long, ...) \
	do                                                    \
	{                                                     \
		if (_long[0] != '\0' && current & _code)          \
		{                                                 \
			if (count--)                                  \
				ft_dprintf(STDERR_FILENO, " ");           \
			ft_dprintf(STDERR_FILENO, "'%s'", _long);     \
		}                                                 \
	} while (0);

#define MATCH_SHORT_OPTION(_name, _code, _short, _long, _removes, _implies, _sort, ...) \
	case _short:                                                                        \
		if (_sort)                                                                      \
			state.sort_type = (enum sort_type)_sort;                                    \
		state.options |= (enum sort_type)_implies;                                      \
		if (IS_SORT(_code))                                                             \
			state.sort_type = _code;                                                    \
		else                                                                            \
			state.options |= _code;                                                     \
		if (_removes)                                                                   \
			state.options &= ~(_removes);                                               \
		break;

static int	parse_options(int argc, char **argv)
{
	int			i;
	size_t		len;
	uint32_t	count, current;

	len = 0;
	for (i = 1; i < argc; i++)
	{
		current = 0;
		count = 0;
		if (!argv[i] || argv[i][0] != '-')
			continue;
		len = ft_strlen(argv[i]);
		if (ft_strncmp(argv[i], "--", 2) == 0)
		{
			if (len > 2)
			{
				OPTIONS_ITER(MATCH_LONG_OPTION);
				if (!count)
				{
					ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": unrecognized option '%s'\n", argv[i]);
					return (-1);
				}
				if (count >= 2)
				{
					ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": option '%s' is ambiguous; possibilities:", argv[i]);
					OPTIONS_ITER(PRINT_AMBIGUOUS);
					ft_dprintf(STDERR_FILENO, "\n");
					return (-1);
				}
				state.options |= current;
			}
		}
		else
		{
			for (int j = 1; argv[i][j] != '\0'; j++)
			{
				switch (argv[i][j])
				{
				OPTIONS_ITER(MATCH_SHORT_OPTION);
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
	int file_args = 0;
	int	filecount = 0;
	bool word = false;
	char *_eq;

	if (parse_options(argc, argv) != 0)
		exit(EXIT_INVALID_OPTION);
	_eq = NULL;
	for (int i = 1; i < argc; i++)
	{
		_eq = ft_strchr(argv[i], '=');
		if (word)
		{
			word = false;
			continue;
		}
		else if (
					((_eq && ft_strncmp(argv[i], "--format", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], "--format", ft_strlen(argv[i])) == 0)
					|| ((_eq && ft_strncmp(argv[i], "--sort", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], "--sort", ft_strlen(argv[i])) == 0)
				)
		{
			if (!_eq)
			{
				word = true;
				continue;
			}
		}

		if ((argv[i][0] == '-' && ft_strlen(argv[i]) > 1))
			continue;
		file_args++;
		struct Entry *_new_entry = entry_create(argv[i], argv[i]);
		if (!_new_entry)
		{
			state.exit_value = EXIT_FAILURE;
			continue;
		}
		if (is_entry_directory(_new_entry))
			add_element(dirs, _new_entry);
		else
			add_element(files, _new_entry);
		filecount++;
	}
	int dircount = ft_lstsize(*dirs);

	// default path
	if (dircount == 0 && filecount == 0 && file_args == 0)
	{
		struct Entry *_new_entry = entry_create(".", NULL);
		if (do_stat(".", &_new_entry->statbuf) != 0)
			show_errno_error(_new_entry->name);
		else
			add_element(dirs, _new_entry);
	}

	if (dircount > 1 || filecount > 1 || (dircount >= 1 && filecount >= 1 && file_args > 1) || (state.options & OPTION_RECURSIVE) || (filecount > 2))
		state.show_dir_names = true;
	if (state.options & OPTION_REVERSE)
	{
		reverse_list(files);
		reverse_list(dirs);
	}
	return (0);
}

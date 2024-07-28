/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:20:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/28 16:12:06 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#ifdef __GNUC__
# if __has_warning("-Wgnu-zero-variadic-macro-arguments")
#  pragma GCC diagnostic ignored	"-Wgnu-zero-variadic-macro-arguments"
# endif
#endif // __GNUC__

#define DO_FORMATS_ITER(_ITER_F) do { FORMATS_ITER(_ITER_F) } while (0)
#define DO_SORTS_ITER(_ITER_F) do { SORTS_ITER(_ITER_F) } while (0)
#define DO_COLORS_ITER(_ITER_F) do { COLORS_ITER(_ITER_F) } while (0)
#define DO_OPTIONS_ITER(_ITER_F) do { OPTIONS_ITER(_ITER_F) } while (0)

#define _IS_CODE_COLOR(_option_code) (_option_code == OPTION_COLOR_NEVER || _option_code == OPTION_COLOR_AUTO || _option_code == OPTION_COLOR_ALWAYS)
#define _IS_CODE_SORT_TYPE(_option_code) (_option_code == OPTION_SORT_BY_SIZE || _option_code == OPTION_SORT_BY_TIME || _option_code == OPTION_SORT_NONE)

#define PRINT_VALID_ARGUMENTS(_code, ...)							\
	do																\
	{																\
		char *_args[] = {__VA_ARGS__};								\
		size_t _num_args = sizeof(_args) / sizeof(_args[0]);		\
		ft_dprintf(STDERR_FILENO, "  - ");							\
		for (size_t _i = 0; _i < _num_args; ++_i)					\
		{															\
			ft_dprintf(STDERR_FILENO, "‘%s’", _args[_i]);			\
			if (_i + 1 < _num_args)									\
				ft_dprintf(STDERR_FILENO, ", ");					\
		}															\
		ft_dprintf(STDERR_FILENO, "\n");							\
	} while (0);
	
#define MATCH_OPTION_ARGUMENT(_code, ...)							\
	do																\
	{																\
		match = false;												\
		char *_args[] = {__VA_ARGS__};								\
		size_t _num_args = sizeof(_args) / sizeof(_args[0]);		\
		for (size_t _i = 0; _i < _num_args; ++_i)					\
		{															\
			if (ft_strncmp(word, _args[_i], ft_strlen(word)) == 0)	\
			{														\
				if (_IS_CODE_SORT_TYPE(_code))						\
					state.sort_type = (enum SortType)_code;			\
				else if (_IS_CODE_COLOR(_code))						\
					state.color_type = (enum ColorType)_code;		\
				else												\
					state.options |= _code;							\
				state.options |= _code;								\
				match = true;										\
				break ;												\
			}														\
		}															\
		if (match)													\
			count++;												\
	} while (0);

static inline int match_word(char *word, char *option)
{
	if (!word)
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": option '%s' requires an argument\n", option);
		return (-1);
	}

	uint32_t	count = 0;
	bool		match;
	if (ft_strcmp(option, "--format") == 0)
		DO_FORMATS_ITER(MATCH_OPTION_ARGUMENT);
	else if (ft_strcmp(option, "--sort") == 0)
		DO_SORTS_ITER(MATCH_OPTION_ARGUMENT);
	else if (ft_strcmp(option, "--color") == 0)
		DO_COLORS_ITER(MATCH_OPTION_ARGUMENT);
	if (count != 1)
	{
		if (count == 0)
			ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": invalid argument '%s' for '%s'\nValid arguments are:\n", word, option);
		else
			ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": ambiguous argument '%s' for '%s'\nValid arguments are:\n", word, option);
		if (ft_strcmp(option, "--format") == 0) 
			DO_FORMATS_ITER(PRINT_VALID_ARGUMENTS);
		else if (ft_strcmp(option, "--sort") == 0) 
			DO_SORTS_ITER(PRINT_VALID_ARGUMENTS);
		else if (ft_strcmp(option, "--color") == 0)
			DO_COLORS_ITER(PRINT_VALID_ARGUMENTS);
	}
	if (count == 1)
		return (0);
	return (-1);
}

#define MATCH_LONG_OPTION(_name, _code, _short, _long, _removes, ...)																				\
	do																																				\
	{																																				\
		if (!argv[i])																																\
			return (0);																																\
		char *_eq = ft_strchr(argv[i], '=');																										\
		size_t _len_to_eq;																															\
		if (_eq)																																	\
			_len_to_eq = _eq - argv[i];																												\
		else																																		\
			_len_to_eq = len;																														\
		if (																																		\
			(_code == OPTION_FORMAT && ((_eq && ft_strncmp(argv[i], "--format", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], _long, len) == 0)) ||	\
			(_code == OPTION_SORT   && ((_eq && ft_strncmp(argv[i], "--sort",   (_eq - argv[i])) == 0) || ft_strncmp(argv[i], _long, len) == 0)) ||	\
			(_code == OPTION_COLOR  && ((_eq && ft_strncmp(argv[i], "--color",  (_eq - argv[i])) == 0) || ft_strncmp(argv[i], _long, len) == 0))	\
		)																																			\
		{																																			\
			/* Color is 'always' when no arguments are specified */\
			if (ft_strncmp(argv[i], "--color", len) == 0 && !_eq)\
			{\
				state.color_type = color_always;\
				should_continue = true;\
				break;\
			}\
			char *_word;																															\
			if (!_eq)																																\
			{																																		\
				i++;																																\
				_word = argv[i];																													\
			}																																		\
			else																																	\
			{																																		\
				len--;																																\
				_word = _eq + 1;																													\
			}																																		\
			if (match_word(_word, _long) == 0)																										\
			{																																		\
				state.options |= _code;																												\
				should_continue = true;																												\
			}																																		\
			else																																	\
				return (-1);																														\
		}																																			\
		else if (ft_strncmp(argv[i], _long, _len_to_eq) == 0)																						\
		{																																			\
			if (_eq)																																\
			{																																		\
				ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": option '%s' doesn't allow an argument\n", _long);											\
				return (-1);																														\
			}																																		\
			state.options |= _code;																													\
			if (_removes)																															\
				state.options &= ~(_removes);																										\
			should_continue = true;																													\
		}																																			\
	} while (0);

#define MATCH_SHORT_OPTION(_name, _code, _short, _long, _removes, _implies, _sort, ...)	\
	case _short:																		\
		if (_sort)																		\
			state.sort_type = (enum SortType)_sort;										\
		state.options |= (enum SortType)_implies;										\
		if (_IS_CODE_SORT_TYPE(_code))													\
			state.sort_type = _code;													\
		else																			\
			state.options |= _code;														\
		if (_code == OPTION_DIRECTORY_ORDER)											\
		{																				\
			state.sort_type = sort_none;												\
			state.color_type = color_never;												\
		}																				\
		if (_removes)																	\
			state.options &= ~(_removes);												\
		break;

#define PRINT_AMBIGUOUS(_name, _code, _short, _long, ...)	\
	do														\
	{														\
		if (_long[0] != '\0' && options & _code)			\
		{													\
			if (count--)									\
				ft_dprintf(STDERR_FILENO, " ");				\
			ft_dprintf(STDERR_FILENO, "'%s'", _long);		\
		}													\
	} while (0);

#define _IS_VALID_OPTION(_name, _code, _short, _long, ...)						\
	do {																		\
		if (_long[0] != '\0' && ft_strncmp(_long, arg, len) == 0)				\
		{																		\
			options |= _code;													\
			count++;															\
		}																		\
	} while (0);

int	check_ambiguous(const char *arg)
{
	uint32_t count, options;
	size_t	len = 0;
	char	*eq = ft_strchr(arg, '=');

	if (!arg)
		return (0);
	if (eq)
		len = eq - arg;
	else
		len = ft_strlen(arg);

	count = 0;
	options = 0;
	DO_OPTIONS_ITER(_IS_VALID_OPTION);
	if (count > 1)
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": option '%s' is ambiguous; possibilities:", arg);
		DO_OPTIONS_ITER(PRINT_AMBIGUOUS);
		ft_dprintf(STDERR_FILENO, "\n");
		return (-1);
	}
	return (0);
}

static int	parse_options(int argc, char **argv)
{
	int			i, tmp;
	size_t		len;
	bool		should_continue;

	len = 0;
	for (i = 1; i < argc; i++)
	{
		should_continue = false;
		if (!argv[i] || argv[i][0] != '-')
			continue;
		len = ft_strlen(argv[i]);
		if (ft_strncmp(argv[i], "--", 2) == 0)
		{
			if (len > 2)
			{
				if (check_ambiguous(argv[i]) != 0)
					return (-1);
				tmp = i;
				DO_OPTIONS_ITER(MATCH_LONG_OPTION);
				if (should_continue)
					continue;
				ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": unrecognized option '%s'\n", argv[tmp]);
				return (-1);
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
	if (state.options & OPTION_DIRECTORY_ORDER)
		state.options &= ~(OPTION_REVERSE);
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
					((_eq && ft_strncmp(argv[i], "--format", (_eq - argv[i])) == 0) || ft_strncmp(argv[i], "--format", ft_strlen(argv[i])) == 0) ||
					((_eq && ft_strncmp(argv[i], "--sort",   (_eq - argv[i])) == 0) || ft_strncmp(argv[i], "--sort",   ft_strlen(argv[i])) == 0) ||
					((_eq && ft_strncmp(argv[i], "--color",  (_eq - argv[i])) == 0) || ft_strncmp(argv[i], "--color",  ft_strlen(argv[i])) == 0)
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
		struct Entry *_new_entry = entry_create(".", ".");
		if (_new_entry)
			add_element(dirs, _new_entry);
	}

	if (dircount > 1 || filecount > 1 || (dircount >= 1 && filecount >= 1 && file_args > 1) || (state.options & OPTION_RECURSIVE) || (filecount > 2))
		state.show_dir_names = true;
	if (state.options & OPTION_REVERSE)
	{
		reverse_list(files);
		reverse_list(dirs);
	}
	if (state.color_type == color_always || (state.color_type == color_auto && isatty(STDOUT_FILENO)))
		state.show_colors = true;
	return (0);
}

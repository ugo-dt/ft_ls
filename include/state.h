/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/24 14:21:22 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <libft.h>
# include <stdbool.h>
# include <time.h>

# define OPTIONS_ITER(_ITER_F, ...)                                                                                                      \
	/*      NAME				CODE	SHORT LONG				REMOVES_OPTION		IMPLIES_OPTION		IMPLIES_SORT */                  \
	_ITER_F(ALL,				0x1,	'a', "--all",			OPTION_ALMOST_ALL,	0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(ALMOST_ALL,			0x2,	'A', "--almost-all",	OPTION_ALL, 		0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(DIRECTORY_ORDER,	0x4,	'f', "\0",				0x0,				OPTION_ALL,			OPTION_SORT_NONE,	__VA_ARGS__) \
	_ITER_F(FORMAT,				0x8,	0,   "--format",		0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(HIDE_OWNER,			0x10,	'g', "\0",				0x0,				OPTION_LONG,		0x0,				__VA_ARGS__) \
	_ITER_F(LONG,				0x20,	'l', "\0",				0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(HIDE_GROUP,			0x40,	'o', "\0",				0x0,				OPTION_LONG,		0x0,				__VA_ARGS__) \
	_ITER_F(REVERSE,			0x80,	'r', "--reverse",		0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(RECURSIVE,			0x100,	'R', "--recursive",		0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(PRINT_SIZE,			0x200,	's', "--size",			0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(SORT,				0x400,	1,   "--sort",			0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(SORT_BY_SIZE,		0x800,	'S', "\0",				0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(SORT_BY_TIME,		0x1000,	't', "\0",				0x0,				0x0,				0x0,				__VA_ARGS__) \
	_ITER_F(SORT_NONE,			0x2000,	'U', "\0",				0x0,				0x0,				0x0,				__VA_ARGS__)

# define FORMATS_ITER(_ITER_F, ...)          \
	_ITER_F(LONG,    OPTION_LONG, "long")    \
	_ITER_F(VERBOSE, OPTION_LONG, "verbose")

# define SORTS_ITER(_ITER_F, ...)              \
	_ITER_F(NONE, OPTION_SORT_NONE, "none")    \
	_ITER_F(SIZE, OPTION_SORT_BY_SIZE, "size") \
	_ITER_F(TIME, OPTION_SORT_BY_TIME, "time")

# define DECL_OPTION_ENUM_MEMBER(_name, _code, ...)	OPTION_##_name = _code,

enum Option
{
	OPTIONS_ITER(DECL_OPTION_ENUM_MEMBER,)
	LAST_OPTION = OPTION_SORT_NONE,
};

enum sort_type
{
	sort_by_name = 0x0, // default
	sort_by_time = OPTION_SORT_BY_TIME,
	sort_by_size = OPTION_SORT_BY_SIZE,
	sort_none    = OPTION_SORT_NONE,
};

struct State
{
	int				exit_value;
	uint32_t		options;
	enum sort_type	sort_type;
	t_list			*files;
	bool			show_dir_names;
	struct timespec	current_time;
	bool			add_newline;

	struct
	{
		int	file_blocks;
		int	owner;
		int	group;
		int	nlink;
		int	file_size;
		int	major_device_number;
		int	minor_device_number;
	}width;
};

extern struct State	state;

#endif // STATE_H

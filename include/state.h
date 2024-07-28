/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/28 16:14:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# ifdef __APPLE__
#  define _DARWIN_C_SOURCE	1
#  define BLOCKS_SHIFT_BY	0
#  define st_mtime			st_mtimespec
# elif __linux__
#  define _DEFAULT_SOURCE	1
#  define BLOCKS_SHIFT_BY	1
# endif

# include <dirent.h>
# include <errno.h>
# include <libft.h>
# include <grp.h>
# include <pwd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>

void	*ft_xmalloc(size_t size);
void	*ft_xcalloc(size_t size);
char	*ft_xstrdup(const char *s);

# define PROGRAM_NAME	"ft_ls"
# define NSEC_PER_SEC	1000000000

# define OPTIONS_ITER(_ITER_F, ...)																																	\
	/*      OPTION_NAME				CODE		SHORT	LONG				REMOVES_OPTION						IMPLIES_OPTION	IMPLIES_SORT */						\
	_ITER_F(OPTION_ALL,				0x1,		'a',	"--all",			OPTION_ALMOST_ALL,					0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_ALMOST_ALL,		0x2,		'A',	"--almost-all",		OPTION_ALL, 						0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_COLOR,			0x4,		0,  	"--color",			0x0, 								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_COLOR_NEVER,		0x8,		1,  	"\0",				0x0, 								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_COLOR_ALWAYS,	0x10,		2,  	"\0",				0x0, 								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_COLOR_AUTO,		0x20,		3,  	"\0",				0x0, 								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_DIRECTORY_ORDER,	0x40,		'f',	"\0",				(OPTION_LONG | OPTION_PRINT_SIZE),	OPTION_ALL,		OPTION_SORT_NONE,	__VA_ARGS__)	\
	_ITER_F(OPTION_FORMAT,			0x80,		4,		"--format",			0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_HIDE_OWNER,		0x100,		'g',	"\0",				0x0,								OPTION_LONG,	0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_LONG,			0x200,		'l',	"\0",				0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_HIDE_GROUP,		0x400,		'o',	"\0",				0x0,								OPTION_LONG,	0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_REVERSE,			0x800,		'r',	"--reverse",		0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_RECURSIVE,		0x1000,		'R',	"--recursive",		0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_PRINT_SIZE,		0x2000,		's',	"--size",			0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_SORT,			0x4000,		5,		"--sort",			0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_SORT_BY_SIZE,	0x8000,		'S',	"\0",				0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_SORT_BY_TIME,	0x10000,	't',	"\0",				0x0,								0x0,			0x0,				__VA_ARGS__)	\
	_ITER_F(OPTION_SORT_NONE,		0x20000,	'U',	"\0",				0x0,								0x0,			0x0,				__VA_ARGS__)

# define COLORS_ITER(_ITER_F)									\
	_ITER_F(OPTION_COLOR_ALWAYS,	"always", "yes", "force")	\
	_ITER_F(OPTION_COLOR_NEVER,		"never", "no", "none")		\
	_ITER_F(OPTION_COLOR_AUTO,		"auto", "tty", "if-tty")

# define FORMATS_ITER(_ITER_F)					\
	_ITER_F(OPTION_LONG,	"verbose", "long")	\

# define SORTS_ITER(_ITER_F)				\
	_ITER_F(OPTION_SORT_NONE,		"none")	\
	_ITER_F(OPTION_SORT_BY_SIZE,	"size")	\
	_ITER_F(OPTION_SORT_BY_TIME,	"time")

# define DECL_OPTION_ENUM_MEMBER(_name, _code, ...)	_name = _code,

enum Option
{
	OPTIONS_ITER(DECL_OPTION_ENUM_MEMBER,)
	LAST_OPTION = OPTION_SORT_NONE,
};

enum SortType
{
	sort_by_name = 0x0, // default
	sort_by_time = OPTION_SORT_BY_TIME,
	sort_by_size = OPTION_SORT_BY_SIZE,
	sort_none    = OPTION_SORT_NONE,
};

enum ColorType
{
	color_never = OPTION_COLOR_NEVER, // default
	color_auto = OPTION_COLOR_AUTO,
	color_always = OPTION_COLOR_ALWAYS
};

struct LS_Colors
{
	char	*no;
	char	*fi;
	char	*di;
	char	*ln;
	char	*pi;
	char	*door;
	char	*bd;
	char	*cd;
	char	*or;
	char	*so;
	char	*su;
	char	*sg;
	char	*tw;
	char	*ow;
	char	*st;
	char	*ex;
	char	*mi;
	char	*lc;
	char	*rc;
	char	*ec;
	char	**extensions;
};

struct State
{
	int					exit_value;
	uint32_t			options;
	enum SortType		sort_type;
	enum ColorType		color_type;
	t_list				*files;
	bool				show_dir_names;
	struct timespec		current_time;
	bool				add_newline;
	bool				show_colors;
	bool				first;

	struct LS_Colors	colors;

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

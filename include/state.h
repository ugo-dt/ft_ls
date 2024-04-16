/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/16 20:58:55 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <libft.h>
# include <stdbool.h>
# include <time.h>

# define OPTION_ALL				0x1 // -a, --all
# define OPTION_ALMOST_ALL		0x2 // -A, --almost-all
# define OPTION_LONG			0x4 // -l, --long
# define OPTION_REVERSE			0x8 // -r, --reverse
# define OPTION_RECURSIVE		0x10 //
# define OPTION_DONT_SHOW_OWNER	0x20 // -g
# define OPTION_DONT_SHOW_GROUP	0x40 // -o
# define OPTION_PRINT_SIZE		0x80 // -s, --size

enum sort_type
{
	sort_by_name,
	sort_by_time,
	sort_by_size,
	sort_none,
};

typedef void	(*LstIterFunction)(void *);

struct State
{
	int				exit_value;
	unsigned int	options;
	enum sort_type	sort_type;
	t_list			*files;
	bool			show_dir_names;
	struct timespec	current_time;

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

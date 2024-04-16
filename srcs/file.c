/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:20:03 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/22 12:03:50 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int do_stat(const char *path, struct stat *buf)
{
	if (state.options & OPTION_LONG)
		return (lstat(path, buf));
	return (stat(path, buf));
}

void	print_file_type(mode_t mode)
{
	switch (mode & S_IFMT)
	{
	case S_IFREG:
		ft_putchar('-');
		break;
	case S_IFBLK:
		ft_putchar('b');
		break;
	case S_IFCHR:
		ft_putchar('c');
		break;
	case S_IFDIR:
		ft_putchar('d');
		break;
	case S_IFLNK:
		ft_putchar('l');
		break;
	case S_IFSOCK:
		ft_putchar('s');
		break;
	case S_IFIFO:
		ft_putchar('p');
		break;
	default:
		ft_putchar('?');
		break;
	}
}

void print_owner_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	if (mode & S_IXUSR)
	{
		if (mode & S_ISUID)
			ft_putchar('s');
		else
			ft_putchar('x');
	}
	else
	{
		if (mode & S_ISUID)
			ft_putchar('S');
		else
			ft_putchar('-');
	}
}

void print_group_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	if (mode & S_IXGRP)
	{
		if (mode & S_ISGID)
			ft_putchar('s');
		else
			ft_putchar('x');
	}
	else
	{
		if (mode & S_ISGID)
			ft_putchar('S');
		else
			ft_putchar('-');
	}
}

void print_other_permissions(mode_t mode)
{
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_IXOTH)
	{
		if (mode & S_ISVTX)
			ft_putchar('t');
		else
			ft_putchar('x');
	}
	else
	{
		if (mode & S_ISVTX)
			ft_putchar('T');
		else
			ft_putchar('-');
	}
}

void print_date(struct stat *statbuf)
{
	struct timespec when_timespec;
	struct timespec six_months_ago;
	bool recent;

	when_timespec = statbuf->st_mtim;
	/* If the file appears to be in the future, update the current
	   time, in case the file happens to have been modified since
	   the last time we checked the clock.  */
	if (timespec_cmp(state.current_time, when_timespec) < 0)
	{
		state.current_time.tv_sec = time(NULL);
		state.current_time.tv_nsec = when_timespec.tv_nsec;
	}

	/* Consider a time to be recent if it is within the past six months.
	   A Gregorian year has 365.2425 * 24 * 60 * 60 == 31556952 seconds
	   on the average. Write this value as an integer constant to
	   avoid floating point hassles.
	*/
	six_months_ago.tv_sec = state.current_time.tv_sec - 31556952 / 2;
	// six_months_ago.tv_nsec = state.current_time.tv_nsec;

	recent = (timespec_cmp(six_months_ago, when_timespec) <= 0 && timespec_cmp(when_timespec, state.current_time) <= 0);
	char *time_str = ctime(&statbuf->st_mtime);
	size_t len = ft_strlen(time_str);
	write(STDOUT_FILENO, time_str + 4, 6);
	ft_putchar(' ');
	if (recent)
	{
		time_str[len - 9] = '\0';
		ft_putstr(time_str + 11);
	}
	else
	{
		time_str[len - 1] = '\0';
		ft_putstr(time_str + 19);
	}
}

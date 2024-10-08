/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:24:23 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 13:31:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "state.h"

static inline void	show_errno_error(const char *path)
{
	switch (errno)
	{
	case EACCES:
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": cannot open directory '%s': %s\n", path, strerror(errno));
		break;
	default:
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": cannot access '%s': %s\n", path, strerror(errno));
		break;
	}
	state.exit_value = EXIT_FAILURE;
}

int		do_stat(const char *path, struct stat *buf, bool *is_link);
void	print_file_type(mode_t mode);
void	print_owner_permissions(mode_t mode);
void	print_group_permissions(mode_t mode);
void	print_other_permissions(mode_t mode);
void	print_date(struct stat *statbuf);

int		timespec_cmp(struct timespec ts1, struct timespec ts2);

#endif // FILE_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:47:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:31:58 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

const char *get_entry_color(mode_t mode)
{
	switch (mode & S_IFMT)
	{
	case S_IFREG: // Normal file
		break;
	case S_IFBLK: // Block device
		break;
	case S_IFCHR: // Character device
		break;
	case S_IFDIR: // Directory
		break;
	case S_IFLNK: // Symbolic link
		break;
	case S_IFSOCK: // Socket
		break;
	case S_IFIFO: // Named pipe
		break;
	default:
		break;
	}
	return "\033[91m";
}

void	parse_dircolors(const char *dircolors)
{
	const char *p = dircolors;
	(void)p;
}

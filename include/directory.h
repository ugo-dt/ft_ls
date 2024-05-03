/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:27:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/03 13:30:20 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H

# include "entry.h"
# include "list.h"
# include "state.h"

# include <dirent.h>
# include <errno.h>
# include <libft.h>
# include <string.h>

void 	print_dir(t_list *file);

#endif // DIRECTORY_H

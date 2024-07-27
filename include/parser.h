/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:22:37 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 15:09:47 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "entry.h"
# include "file.h"
# include "list.h"
# include "state.h"

# define EXIT_INVALID_OPTION	2

int	parse_arguments(int argc, char **argv, t_list **files, t_list **dirs);

#endif // PARSER_H

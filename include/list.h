/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:31:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:27:19 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "entry.h"
# include "parser.h"
# include "directory.h"

void	add_element(t_list **list, struct Entry *content);
void	reverse_list(t_list **list);
void	list_contents(t_list *list);

#endif // LIST_H

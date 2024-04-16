/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:12:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/13 13:14:01 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*xmalloc(size_t size)
{
	void	*p = malloc(size);
	if (!p)
	{
		ft_putendl_fd("out of memory", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

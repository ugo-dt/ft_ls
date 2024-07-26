/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:12:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/02 18:54:01 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libft.h>
# include <stdlib.h>

void	*ft_xmalloc(size_t size)
{
	void	*p = malloc(size);
	if (!p)
	{
		ft_putendl_fd("\nfatal: out of memory", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	*ft_xcalloc(size_t size)
{
	void	*p = ft_xmalloc(size);
	ft_bzero(p, size);
	return (p);
}

char	*ft_xstrdup(const char *s)
{
	char	*p = ft_strdup(s);
	if (!p)
	{
		ft_putendl_fd("\nfatal: out of memory", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

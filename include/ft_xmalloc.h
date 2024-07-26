/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:55:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/25 12:51:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_XMALLOC_H
# define FT_XMALLOC_H

void	*ft_xmalloc(size_t size);
void	*ft_xcalloc(size_t size);
char	*safe_strdup(const char *s);

# define ft_strdup safe_strdup

#endif // FT_XMALLOC_H

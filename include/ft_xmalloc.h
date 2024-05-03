/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:55:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/02 18:55:46 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_XMALLOC_H
# define FT_XMALLOC_H

# include <libft.h>
# include <stdlib.h>

void	*ft_xmalloc(size_t size);
void	*ft_xcalloc(size_t size);

#endif // FT_XMALLOC_H

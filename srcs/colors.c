/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:47:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/28 15:51:58 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

char	**get_key(LS_Colors *colors, const char *key, size_t len)
{
	if (!key)
		return NULL;
	if (ft_strncmp(key, "no", len) == 0)
		return &colors->no;
	if (ft_strncmp(key, "fi", len) == 0)
		return &colors->fi;
	if (ft_strncmp(key, "di", len) == 0)
		return &colors->di;
	if (ft_strncmp(key, "ln", len) == 0)
		return &colors->ln;
	if (ft_strncmp(key, "pi", len) == 0)
		return &colors->pi;
	if (ft_strncmp(key, "do", len) == 0)
		return &colors->door;
	if (ft_strncmp(key, "bd", len) == 0)
		return &colors->bd;
	if (ft_strncmp(key, "cd", len) == 0)
		return &colors->cd;
	if (ft_strncmp(key, "or", len) == 0)
		return &colors->or;
	if (ft_strncmp(key, "so", len) == 0)
		return &colors->so;
	if (ft_strncmp(key, "su", len) == 0)
		return &colors->su;
	if (ft_strncmp(key, "sg", len) == 0)
		return &colors->sg;
	if (ft_strncmp(key, "tw", len) == 0)
		return &colors->tw;
	if (ft_strncmp(key, "ow", len) == 0)
		return &colors->ow;
	if (ft_strncmp(key, "st", len) == 0)
		return &colors->st;
	if (ft_strncmp(key, "ex", len) == 0)
		return &colors->ex;
	if (ft_strncmp(key, "mi", len) == 0)
		return &colors->mi;
	if (ft_strncmp(key, "lc", len) == 0)
		return &colors->lc;
	if (ft_strncmp(key, "rc", len) == 0)
		return &colors->rc;
	if (ft_strncmp(key, "ec", len) == 0)
		return &colors->ec;
	return NULL;
}

void	parse_dircolors(LS_Colors *colors, const char *p)
{
	char	**arr;
	char	**key;

	arr = ft_split(p, ':');
	ft_memset(colors, 0, sizeof(*colors));
	key = NULL;
	for (int i = 0; arr[i]; i++)
	{
		p = arr[i];
		if (*p == '*')
		{
			key = NULL;
			// todo: extensions
		}
		else
		{
			p += ft_strcspn(p, "=\t\n\v\f\r");
			if (p[0] != '=')
				continue;
			key = get_key(colors, arr[i], p - arr[i]);
			if (!key)
				continue;
			p++;
			*key = ft_strjoin_3("\033[", p, "m");
		}
	}
}

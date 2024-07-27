/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:47:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 14:56:48 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

char	**get_key(LS_Colors *colors, const char *key, size_t len)
{
	if (!key)
		return NULL;
	// write(1, key, len);
	// ft_putchar('\n');
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

const char	*get_color_string(int code)
{
	switch (code)
	{
		case 0:		return COLOR_0;
		case 1:		return COLOR_1;
		case 2:		return COLOR_2;
		case 3:		return COLOR_3;
		case 4:		return COLOR_4;
		case 5:		return COLOR_5;
		case 6:		return COLOR_6;
		case 7:		return COLOR_7;
		case 8:		return COLOR_8;
		case 39:	return COLOR_39;
		case 31:	return COLOR_31;
		case 32:	return COLOR_32;
		case 33:	return COLOR_33;
		case 34:	return COLOR_34;
		case 35:	return COLOR_35;
		case 36:	return COLOR_36;
		case 37:	return COLOR_37;
		case 40:	return COLOR_40;
		case 41:	return COLOR_41;
		case 42:	return COLOR_42;
		case 43:	return COLOR_43;
		case 44:	return COLOR_44;
		case 45:	return COLOR_45;
		case 46:	return COLOR_46;
		case 47:	return COLOR_47;
		case 90:	return COLOR_90;
		case 91:	return COLOR_91;
		case 92:	return COLOR_92;
		case 93:	return COLOR_93;
		case 94:	return COLOR_94;
		case 95:	return COLOR_95;
		case 96:	return COLOR_96;
		case 97:	return COLOR_97;
		case 100:	return COLOR_100;
		case 101:	return COLOR_101;
		case 102:	return COLOR_102;
		case 103:	return COLOR_103;
		case 104:	return COLOR_104;
		case 105:	return COLOR_105;
		case 106:	return COLOR_106;
		case 107:	return COLOR_107;
		default: return "";
	}
	return "";
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
			// extension
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

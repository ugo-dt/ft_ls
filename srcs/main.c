/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:32:13 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct State state;

int main(int argc, char **argv)
{
	t_list *files, *dirs;

	files = NULL;
	dirs = NULL;
	ft_memset(&state, 0, sizeof(state));
	state.color_type = color_never;
	parse_arguments(argc, argv, &files, &dirs);
	if (state.show_colors)
	{
	}
	list_contents(files);
	list_contents(dirs);
	ft_lstclear(&files, entry_destroy);
	ft_lstclear(&dirs, entry_destroy);
	return (state.exit_value);
}

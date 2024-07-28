/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:32:13 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/28 15:52:02 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct State state;

void	clear_dircolors()
{
	if (state.colors.no)
		free(state.colors.no);
	if (state.colors.fi)
		free(state.colors.fi);
	if (state.colors.di)
		free(state.colors.di);
	if (state.colors.ln)
		free(state.colors.ln);
	if (state.colors.pi)
		free(state.colors.pi);
	if (state.colors.door)
		free(state.colors.door);
	if (state.colors.bd)
		free(state.colors.bd);
	if (state.colors.cd)
		free(state.colors.cd);
	if (state.colors.or)
		free(state.colors.or);
	if (state.colors.so)
		free(state.colors.so);
	if (state.colors.su)
		free(state.colors.su);
	if (state.colors.sg)
		free(state.colors.sg);
	if (state.colors.tw)
		free(state.colors.tw);
	if (state.colors.ow)
		free(state.colors.ow);
	if (state.colors.st)
		free(state.colors.st);
	if (state.colors.ex)
		free(state.colors.ex);
	if (state.colors.mi)
		free(state.colors.mi);
	if (state.colors.lc)
		free(state.colors.lc);
	if (state.colors.rc)
		free(state.colors.rc);
	if (state.colors.ec)
		free(state.colors.ec);
	// if (state.colors.extensions)
	// 	free(state.colors.extensions);
}

int main(int argc, char **argv)
{
	t_list *files, *dirs;

	files = NULL;
	dirs = NULL;
	ft_memset(&state, 0, sizeof(state));
	parse_dircolors(&state.colors, getenv("LS_COLORS"));
	state.color_type = color_never;
	state.first = true;
	parse_arguments(argc, argv, &files, &dirs);
	list_contents(files);
	list_contents(dirs);
	ft_lstclear(&files, entry_destroy);
	ft_lstclear(&dirs, entry_destroy);
	clear_dircolors();
	return (state.exit_value);
}

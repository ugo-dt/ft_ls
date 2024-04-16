/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:32:13 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/16 13:44:28 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct State state;

int main(int argc, char **argv)
{
	t_list *files = NULL;
	t_list *dirs = NULL;
	int	add_newline = 0;

	ft_memset(&state, 0, sizeof(state));
	parse_arguments(argc, argv, &files, &dirs);
	list_contents(files, &add_newline);
	list_contents(dirs, &add_newline);
	ft_lstclear(&files, (LstIterFunction)entry_destroy);
	ft_lstclear(&dirs, (LstIterFunction)entry_destroy);
	return (state.exit_value);
}

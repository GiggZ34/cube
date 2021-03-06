/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:41:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/02 14:49:50 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		if (ft_load(av[1], &game) != 0)
			return (FAIL_EXIT);
		if (!game.file->error_code)
			ft_update_loop(&game);
		ft_clear_file(game.file, -1, 0);
		free(game.window);
		free(game.mlx);
	}
//	else
//		ft_error_file(game.file, 8, "");

	return (0);
}

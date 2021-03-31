/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:41:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/31 21:21:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 || (ac == 3 && !ft_strncmp(av[2], "--save", 6)))
	{
		ft_bzero(&game, sizeof(t_game));
		if (ac == 3)
		{
			game.save_picture = 1;
			game.exit = 1;
		}
		ft_load(av[1], &game);
		printf("\033[32mRUN GAME\n\033[0m");
		ft_game_loop(&game);
	}
	else
	{
		printf("Error\ninvalid argument\n");
		return (arguments_error);
	}
	return (succes);
}

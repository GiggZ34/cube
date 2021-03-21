/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:41:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 16:52:16 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 || (ac == 3 && !ft_strncmp(av[2], "--save", 6)))
	{
		ft_load(av[1], &game);
		ft_game_loop(&game);
	}
	else
	{
		printf("Error\ninvalid argument\n");
		return (FAIL_EXIT);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:41:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/26 10:20:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void		line_drawing(int x1, int y1, int x2, int y2, void* mlx, void *window)
// {
// 	double dx = x2 - x1;
// 	double dy = y2 - y1;
// 	double e;
// 	if (dx != 0)
// 	{
// 		if (dx > 0)
// 		{
// 			if (dy != 0)
// 			{
// 				if (dy > 0)
// 				{
// 					if (dx >= dy)
// 					{
// 						e = dx;
// 						dx *= 2;
// 						dy *= 2;
// 						while (x1 != x2)
// 						{
// 							mlx_pixel_put(mlx, window, x1, y1, ft_color_generate(255, 0, 0, 0));
// 							x1++;
// 							if ((e -= dy) < 0)
// 							{
// 								y1++;
// 								e += dx;
// 							}
// 						}
// 					}
// 					else
// 					{
// 						e = dy;
// 						dy *= 2;
// 						dx *= 2;
// 						while (y1 != y2)
// 						{
// 							mlx_pixel_put(mlx, window, x1, y1, ft_color_generate(255, 0, 0, 0));
// 							y1++;
// 							if ((e -= dx) < 0)
// 							{
// 								x1++;
// 								e += dy;
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }

int				main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		if (ft_load(av[1], &game) != 0)
			return (FAIL_EXIT);
		exit(0);
		ft_draw(&game);
		// ft_mini_map(&game);
		mlx_loop(game.mlx);
		ft_clear_file(game.file, -1, 0);
		free(game.window);
		free(game.mlx);
	}
	else
		ft_error_file(game.file, 8, "");

	return (0);
}

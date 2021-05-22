/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:48:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:48:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && !game->player.control.reload)
		game->player.control.shoot = 1;
	else if (button == 2 && !game->player.control.shoot)
		game->player.control.reload = 1;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	mlx_mouse_hide(game->mlx, game->window);
	game->player.control.mouse_diff_x = x - game->player.control.mouse_x_pos;
	game->player.control.mouse_diff_y = y
		- game->player.control.mouse_y_pos + 21;
	mlx_mouse_move(game->window,
		game->screen.width / 2 + 100,
		game->screen.max_y - game->screen.height / 2 - 100);
	mlx_mouse_get_pos(game->window,
		&game->player.control.mouse_x_pos,
		&game->player.control.mouse_y_pos);
	return (0);
}

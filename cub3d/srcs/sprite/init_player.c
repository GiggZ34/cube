/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:13:44 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_player(t_game *game, int x, int y, char dir)
{
	game->player.position.x = x + 0.5;
	game->player.position.y = y + 0.5;
	game->player.position.z = 0.5;
	game->player.state = rest;
	game->player.anim_frame = 0;
	game->player.ammunition = barel_fusil;
	if (dir == 'E')
		game->player.angle_z = -M_PI / 2;
	else if (dir == 'S')
		game->player.angle_z = M_PI;
	else if (dir == 'W')
		game->player.angle_z = M_PI / 2;
	else
		game->player.angle_z = 0;
	game->player.angle_x = 0;
	ft_init_tab_vector(game, game->player.position);
	game->player.live = 100;
	game->player.walk_speed_max = 1.5;
	game->player.run_speed_max = 3;
	game->player.pos_z_min = 0.5;
	game->player.control.mouse_x_pos = game->screen.max_x / 2;
	game->player.control.mouse_y_pos = game->screen.max_y / 2 - 22;
	game->player.control.mouse_x = game->player.control.mouse_x_pos;
	game->player.control.mouse_y = game->player.control.mouse_y_pos;
	return (0);
}

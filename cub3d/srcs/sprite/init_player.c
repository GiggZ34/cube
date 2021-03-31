/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/31 19:00:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_player(t_game *game, int x, int y, char dir)
{
	double	angle;

	game->player.position.x = x + 0.5;
	game->player.position.y = y + 0.5;
	game->player.position.z = 0.5;
	game->player.state = rest;
	game->player.anim_frame = 0;
	game->player.ammunition = barel_fusil;
	ft_init_tab_vector(game, game->player.position);
	if (dir == 'E')
		angle = M_PI / 2;
	else if (dir == 'S')
		angle = M_PI;
	else if (dir == 'W')
		angle = 3 / 2 * M_PI;
	else
		angle = 0;
	game->player.angle_z = angle;
	game->player.angle_x = 0;
	game->player.live = 100;
	game->player.walk_speed_max = 1.5;
	game->player.run_speed_max = 3;
	game->player.control.mouse_x_pos = game->screen.max_x / 2;
	game->player.control.mouse_y_pos = game->screen.max_y / 2 - 22;
	game->player.control.mouse_x = game->player.control.mouse_x_pos;
	game->player.control.mouse_y = game->player.control.mouse_y_pos;
	return (0);
}

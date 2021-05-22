/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:44:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:03:51 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_define_angle_move(t_player *player)
{
	if (player->control.w)
		player->dir_walk = -M_PI / 2;
	else if (player->control.s)
		player->dir_walk = M_PI / 2;
	if (player->control.a)
		player->dir_trans = M_PI;
	else if (player->control.d)
		player->dir_trans = 0;
}

int	ft_update_player(t_game *game, t_player *player)
{
	if (player->control.squat)
		player->pos_z_min = 0.3;
	else
		player->pos_z_min = 0.5;
	ft_define_angle_move(player);
	ft_rotate_player(game, player,
		game->player.control.mouse_diff_x,
		game->player.control.mouse_diff_y);
	game->player.control.mouse_diff_x = 0;
	game->player.control.mouse_diff_y = 0;
	ft_move_player(game, player);
	player_shoot(game, player);
	return (0);
}

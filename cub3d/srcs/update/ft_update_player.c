/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:44:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/02 18:04:08 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_shoot(t_game *game, t_player *player)
{
	int	nb_anim;

	if (player->control.shoot && player->state != shoot)
	{
		play_sound("afplay -v 3 ./sounds/shoot_fusil.mp3 &");
		player->state = shoot;
		player->anim_frame = 0;
		player->ammunition--;
	}
	if (player->control.reload == 1 && player->state != reload)
	{
		player->state = reload;
		player->anim_frame = 0;
		player->ammunition = barel_fusil;
		play_sound("afplay -v 3 ./sounds/reload_fusil.mp3 &");
	}
	else
		player->anim_frame += game->dt.dt * 8;
	nb_anim = ft_define_nb_anim(player->state);
	if ((int)player->anim_frame >= nb_anim && player->control.shoot)
	{
		player->anim_frame = 0;
		player->control.shoot = 0;
		player->state = rest;
		if (player->ammunition == 0)
		{
			player->control.reload = 1;
			player->state = reload;
			player->ammunition = barel_fusil;
			play_sound("afplay -v 3 ./sounds/reload_fusil.mp3 &");
		}
	}
	else if ((int)player->anim_frame >= nb_anim)
	{
		player->anim_frame = 0;
		player->control.reload = 0;
		if (player->state != rest)
			player->state = rest;
	}
	player->arm = &player->gun[player->state][(int)player->anim_frame];
}

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
	ft_shoot(game, player);
	return (0);
}

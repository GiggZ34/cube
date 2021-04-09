/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:01:28 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/08 17:30:59 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_player(t_game *game, t_player *player)
{
	if (player->control.a || player->control.d)
		ft_translation_vector(game, SPEED_MAX,
			&player->walk_speed, player->dir_trans);
	else
		ft_translation_vector(game, -SPEED_MAX,
			&player->walk_speed, player->dir_trans);
	if (player->control.w || player->control.s)
		ft_translation_vector(game, SPEED_MAX,
			&player->trans_speed, player->dir_walk);
	else
		ft_translation_vector(game, -SPEED_MAX,
			&player->trans_speed, player->dir_walk);
	player->vz -= WEIGHTLESSNESS * game->dt.dt;
	player->position.z += player->vz * game->dt.dt;
	if (player->position.z < player->pos_z_min)
		player->position.z = player->pos_z_min;
}

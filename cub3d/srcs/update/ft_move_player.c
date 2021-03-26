/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:01:28 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/23 11:30:33 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_player(t_game *game, t_player *player)
{
	if (player->control.a || player->control.d)
		ft_translation_vector(game, SPEED_MAX, &player->walk_speed, player->dir_trans);
	else
		ft_translation_vector(game, -SPEED_MAX,
									&player->walk_speed, player->dir_trans);
	if (player->control.w || player->control.s)
		ft_translation_vector(game, SPEED_MAX, &player->trans_speed, player->dir_walk);
	else
		ft_translation_vector(game, -SPEED_MAX,
									&player->trans_speed, player->dir_walk);
}

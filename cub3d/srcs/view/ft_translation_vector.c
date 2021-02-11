/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translation_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:54:10 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/09 10:07:33 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_translation_vector(t_game *game, double velocity, double angle)
{
	game->player->walk_volocity = velocity;
	if (game->player->walk_volocity > game->player->walk_speed_max)
		game->player->walk_volocity = game->player->walk_speed_max;
	double y = sin(game->player->angle + angle) * velocity;
	double x = cos(game->player->angle + angle) * velocity;
	game->player->position.y += y;
	game->player->position.x += x;
	return (0);
}

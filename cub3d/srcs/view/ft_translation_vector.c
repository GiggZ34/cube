/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translation_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:54:10 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 02:21:02 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_limit_velocity(t_game *game, int run)
{
	if (!run)
	{
		if (game->player->walk_volocity > game->player->walk_speed_max)
			game->player->walk_volocity = game->player->walk_speed_max;
		else if (game->player->walk_volocity < -(game->player->walk_speed_max))
			game->player->walk_volocity = -(game->player->walk_speed_max);
	}
	else
	{
		if (game->player->walk_volocity > game->player->run_speed_max)
			game->player->walk_volocity = game->player->run_speed_max;
		else if (game->player->walk_volocity < -(game->player->run_speed_max))
			game->player->walk_volocity = -(game->player->run_speed_max);
	}
}

int			ft_translation_vector(t_game *game, double velocity, double angle)
{
	double	x;
	double	y;
	double	final_angle;
	int		run;

	run = game->player->control.run;
	final_angle = game->player->angle_z + angle;
	game->player->walk_volocity += (velocity * game->dt.dt);
//	game->player->angle_y += M_PI / 4 * game->dt.dt;	Faire animation de marche
	ft_limit_velocity(game, run);
	if ((game->player->collide.bottom_bool == 1 && (final_angle < M_PI / 2 || final_angle > 3 / 4 * M_PI)) ||
		(game->player->collide.top_bool == 1 && (final_angle > M_PI / 2 && final_angle < 3 / 4 * M_PI)))
		y = 0;
	else
		y = sin(final_angle) * game->player->walk_volocity;
	if ((game->player->collide.left_bool == 1 && final_angle < M_PI) ||
		(game->player->collide.right_bool == 1 && final_angle > M_PI))
		x = 0;
	else
		x = cos(final_angle) * game->player->walk_volocity;
	game->player->position.y += (y * game->dt.dt);
	game->player->position.x += (x * game->dt.dt);
	return (0);
}

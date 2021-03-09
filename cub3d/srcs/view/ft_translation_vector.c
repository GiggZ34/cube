/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translation_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:54:10 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 16:37:06 by grivalan         ###   ########lyon.fr   */
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
	double	addx;
	double	addy;

	addy = 0.1;
	addx = 0.1;
	final_angle = game->player->angle_z + angle;
	game->player->walk_volocity += (velocity * game->dt.dt);
	ft_limit_velocity(game, game->player->control.run);
	y = sin(final_angle) * game->player->walk_volocity;
	x = cos(final_angle) * game->player->walk_volocity;
	if (y < 0)
		addy *= -1;
	if (game->file->map[(int)(game->player->position.y +
			(y * game->dt.dt) + addy)][(int)(game->player->position.x)] != '1')
		game->player->position.y += (y * game->dt.dt);
	if (x < 0)
		addx *= -1;
	if (game->file->map[(int)(game->player->position.y)]
			[(int)(game->player->position.x + (x * game->dt.dt) + addx)] != '1')
		game->player->position.x += (x * game->dt.dt);
	return (0);
}

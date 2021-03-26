/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translation_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:54:10 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/23 11:30:38 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_limit_speed(t_game *game, int run, double *speed)
{
	if (!run || game->player.control.squat)
	{
		if ((*speed) > game->player.walk_speed_max)
			(*speed) = game->player.walk_speed_max;
	}
	else
	{
		if ((*speed) > game->player.run_speed_max)
			(*speed) = game->player.run_speed_max;
	}
}

int			ft_translation_vector(t_game *game, double v, double *speed, double angle)
{
	double	x;
	double	y;
	double	addx;
	double	addy;

	addy = 0.1;
	addx = 0.1;
	(*speed) += (v * game->dt.dt);
	if (*speed < 0)
		*speed = 0;
	ft_limit_speed(game, game->player.control.run, speed);
	y = sin(game->player.angle_z + angle) * (*speed);
	x = cos(game->player.angle_z + angle) * (*speed);
	if (y < 0)
		addy *= -1;
	if (game->file.map[(int)(game->player.position.y +
			(y * game->dt.dt) + addy)][(int)(game->player.position.x)] != '1')
		game->player.position.y += (y * game->dt.dt);
	if (x < 0)
		addx *= -1;
	if (game->file.map[(int)(game->player.position.y)]
			[(int)(game->player.position.x + (x * game->dt.dt) + addx)] != '1')
		game->player.position.x += (x * game->dt.dt);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/02 11:43:17 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	int	fps;

	if (game->dt.time_start > 0)
	{
		gettimeofday(&game->dt.time, NULL);
		game->dt.time_end = 1000000 * game->dt.time.tv_sec
			+ game->dt.time.tv_usec;
		game->dt.dt = (game->dt.time_end - game->dt.time_start);
		game->dt.dt *= 0.000001;
	}
	else
		game->dt.dt = 0.0167;
	gettimeofday(&game->dt.time, NULL);
	game->dt.time_start = 1000000 * game->dt.time.tv_sec
		+ game->dt.time.tv_usec;
	fps = round(1 / game->dt.dt);
	if (fps < FPS_MIN && game->screen.scale < SCALE_MAX)
		game->screen.scale++;
	else if (fps > FPS_MAX && game->screen.scale > 1)
		game->screen.scale--;
	game->dt.dt_str = ft_itoa(fps);
	game->dt.scale_str = ft_itoa(game->screen.scale);
	if (!game->dt.dt_str)
		ft_trash_game(game, allocation_fail, game->file.fd, "\n");
}

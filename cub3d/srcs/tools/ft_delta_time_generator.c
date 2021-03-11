/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 00:56:36 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	int	scale;
	int	fps;

	if (game->dt.time_start > 0)
	{
		gettimeofday(&game->dt.time, NULL);
		game->dt.time_end = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
		game->dt.dt = (game->dt.time_end - game->dt.time_start);
		game->dt.dt /= 1000000;
	}
	else
		game->dt.dt = 0.00167;
	gettimeofday(&game->dt.time, NULL);
	game->dt.time_start = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
	fps = round(1 / game->dt.dt);
	scale = 30 / fps + 1;
	if (scale > game->screen.scale)
		game->screen.scale = scale;
	else if (fps > 30)
		game->screen.scale--;
	game->dt.dt_str = ft_itoa(fps);
	if (!game->dt.dt_str)
		game->file->error_code = 3;
}

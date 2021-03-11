/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 23:48:31 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	int	fps;

	if (game->dt.time_start > 0)
	{
		gettimeofday(&game->dt.time, NULL);
		game->dt.time_end = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
		game->dt.dt = (game->dt.time_end - game->dt.time_start);
		game->dt.dt /= 1000000;
	}
	else
		game->dt.dt = 0.0167;
	gettimeofday(&game->dt.time, NULL);
	game->dt.time_start = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
	fps = round(1 / game->dt.dt);
	game->dt.dt_str = ft_itoa(fps);
	if (fps <= 10)
		game->screen.scale++;
	else if (fps > FPS && game->screen.scale > 0)
		game->screen.scale--;
	if (!game->dt.dt_str)
		game->file->error_code = 3;
}

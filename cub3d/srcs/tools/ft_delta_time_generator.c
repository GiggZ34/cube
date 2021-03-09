/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/08 20:45:09 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	double	time;

	if (game->dt.time_start > 0)
	{
		gettimeofday(&game->dt.time, NULL);
		game->dt.time_end = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
		time = (game->dt.time_end - game->dt.time_start);
		time /= 1000000;
		if (time < 0.0167)
			game->dt.dt = 0.0167;
		else if (time > 0.1)
			game->dt.dt = 0.1;
		else
			game->dt.dt = time;
	}
	else
		game->dt.dt = 0;
	gettimeofday(&game->dt.time, NULL);
	game->dt.time_start = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
	game->dt.dt_str = ft_itoa(round(1 / game->dt.dt));
	if (!game->dt.dt_str)
		game->file->error_code = 3;
}

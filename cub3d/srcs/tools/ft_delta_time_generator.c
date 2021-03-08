/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/08 17:11:56 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	double	time;

	if (game->time_start > 0)
	{
		gettimeofday(&game->time, NULL);
		game->time_end = 1000000 * game->time.tv_sec + game->time.tv_usec;
		time = (game->time_end - game->time_start);
		time /= 1000000;
		if (time < 0.0167)
			game->delta_time = 0.0167;
		else if (time > 0.1)
			game->delta_time = 0.1;
		else
			game->delta_time = time;
	}
	else
		game->delta_time = 0.0167;
	gettimeofday(&game->time, NULL);
	game->time_start = 1000000 * game->time.tv_sec + game->time.tv_usec;
}

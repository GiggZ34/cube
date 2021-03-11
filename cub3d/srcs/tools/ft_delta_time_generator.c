/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delta_time_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:11:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 17:48:36 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_delta_time_generate(t_game *game)
{
	int	scale;
	int	fps;

printf("enter\n");
	if (game->dt.time_start > 0)
	{
		gettimeofday(&game->dt.time, NULL);
		game->dt.time_end = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
		game->dt.dt = (game->dt.time_end - game->dt.time_start);
		game->dt.dt /= 1000000;
		if (game->dt.dt < 0.025)
			game->dt.dt = 0.025;
		else if (game->dt.dt > 0.1)
			game->dt.dt = 0.1;
		printf("exit_if\n");
	}
	else
		game->dt.dt = 0.025;
	gettimeofday(&game->dt.time, NULL);
	game->dt.time_start = 1000000 * game->dt.time.tv_sec + game->dt.time.tv_usec;
	fps = round(1 / game->dt.dt);
	if (fps == 0)
		fps = 1;
	scale = FPS / fps + 1;
	printf("calcul fps\n");
	if (scale > game->screen.scale * 2)
		game->screen.scale = scale;
	else if (fps > FPS)
		game->screen.scale--;
	game->dt.dt_str = ft_itoa(game->screen.scale);//1 / game->dt.dt);
	if (!game->dt.dt_str)
		game->file->error_code = 3;
}

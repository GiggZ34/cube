/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:57:26 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/01 12:26:39 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_resolution(double width, double height)
{
	if (width < MIN_SCREEN_WIDTH || width > MAX_SCREEN_WIDTH
			|| height < MIN_SCREEN_HEIGHT || height > MAX_SCREEN_HEIGHT)
		return (11);
	return (0);
}

static int	ft_change_resolution(t_game *game)
{
	double ratio_x;
	double ratio_y;

	ratio_x = 0;
	ratio_y = 0;
	if (game->screen.width < MIN_SCREEN_WIDTH)
		ratio_x = MIN_SCREEN_WIDTH / game->screen.width;
	else if (game->screen.width > MAX_SCREEN_WIDTH)
		ratio_x = MAX_SCREEN_WIDTH / game->screen.width;
	if (game->screen.height < MIN_SCREEN_HEIGHT)
		ratio_y = MIN_SCREEN_HEIGHT / game->screen.height;
	else if (game->screen.height > MAX_SCREEN_HEIGHT)
		ratio_y = MAX_SCREEN_HEIGHT / game->screen.height;
	if (ratio_x == 0 && ratio_y == 0)
		return (0);
	if (ratio_x > ratio_y)
		ratio_y = ratio_x;
	else
		ratio_x = ratio_y;
	game->screen.width *= ratio_x;
	game->screen.height *= ratio_y;
	return (ft_check_resolution(game->screen.width, game->screen.height));
}

int			ft_check_struct(t_game *game)
{
	if (game->screen.width < 640 || game->screen.width > 2560
			|| game->screen.height < 480 || game->screen.height > 1400)
		if ((game->file->error_code = ft_change_resolution(game)) != 0)
			return (ft_error_file(game->file, game->file->error_code, ""));
	return (0);
}

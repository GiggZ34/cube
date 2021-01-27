/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:21:03 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/20 16:00:26 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				ft_screen(t_game *game)
{
	double	h;

	h = game->screen->width * sqrt(3) / 2;
	game->screen->w_vec = game->screen->width / h / 2;
	game->screen->height_fov = FOV * game->screen->height / game->screen->width;
	if (game->screen->height_fov > FOV)
		game->screen->height_fov = FOV;
	game->screen->h_vec = game->screen->height_fov * game->screen->w_vec / FOV;
}

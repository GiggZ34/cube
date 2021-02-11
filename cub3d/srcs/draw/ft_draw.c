/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/11 13:29:27 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_draw(t_game *game)
{
	int			id;
	int			end;
	t_vector	vec;

	end = game->screen.size * game->screen.height;
	id = -1;
	while (++id < end)
	{
		vec = game->player->view.tab_vectors[id];
		game->screen.color[id] = ft_pixel_color(game, vec);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0);
	return (0);
}

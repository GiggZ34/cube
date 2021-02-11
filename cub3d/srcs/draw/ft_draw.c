/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/09 10:59:43 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_draw(t_game *game)
{
	int			x;
	int			y;
	t_vector	vec;

	y = -1;
	while (++y < game->screen.height)
	{
		x = -1;
		while (++x < game->screen.width)
		{
			vec = game->player->view.tab_vectors[y * game->screen.width + x];
//			game->screen.color[y * game->screen.width + x] = ft_pixel_color(game, vec);
			mlx_pixel_put(game->mlx, game->window, x, y, ft_pixel_color(game, vec));
		}
	}
//	mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0);
	return (0);
}

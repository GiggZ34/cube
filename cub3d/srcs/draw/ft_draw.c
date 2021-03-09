/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 17:39:12 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_draw(void *g)
{
	t_game		*game;
	int			id;
	int			end;
	t_vector	vec;

	game = (t_game *)g;
	end = game->screen.size * game->screen.height;
	id = -1;
	while (++id < end)
	{
		vec = game->player->view.tab_vectors[id];
		if (game->player->angle_x != 0)
			vec = ft_rotate_vector(vec, game->player->angle_x, 'x');
		if (game->player->angle_y != 0)
			vec = ft_rotate_vector(vec, game->player->angle_y, 'y');
		if (game->player->angle_z != 0)
			vec = ft_rotate_vector(vec, game->player->angle_z, 'z');
		game->screen.color[id] = ft_pixel_color(game, vec);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0);
	ft_print_fps(game, game->dt.dt_str);
	return (0);
}

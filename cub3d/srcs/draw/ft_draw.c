/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 00:37:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_drawing_scale(t_game *game, int id, int color)
{
	int	i;
	int	j;
	int	pos;

	i = -1;
	while (++i < game->screen.scale)
	{
		j = -1;
		while (++j < game->screen.scale)
		{
			pos = id + i * game->screen.size + j;
			game->screen.color[pos] = color;
		}
	}
}

void	*ft_draw(void *g)
{
	t_game		*game;
	int			id;
	int			i;
	int			j;
	t_vector	vec;

	game = (t_game *)g;
	j = 0;
	while (j < game->screen.height)
	{
		i = 0;
		while (i < game->screen.size)
		{
			id = j * game->screen.size + i;
			vec = game->player->view.tab_vectors[id];
			if (game->player->angle_x != 0)
				vec = ft_rotate_vector(vec, game->player->angle_x, 'x');
			if (game->player->angle_y != 0)
				vec = ft_rotate_vector(vec, game->player->angle_y, 'y');
			if (game->player->angle_z != 0)
				vec = ft_rotate_vector(vec, game->player->angle_z, 'z');
			ft_drawing_scale(game, id, ft_pixel_color(game, vec));
			i += game->screen.scale;
		}
		j += game->screen.scale;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0);
	ft_print_fps(game, game->dt.dt_str);
	return (0);
}

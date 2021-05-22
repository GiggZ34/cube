/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 18:55:22 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sky_ground_color(t_game *g, t_vector *vec, t_texture t, t_plane p)
{
	double		size;
	t_dot		inter;
	int			x;
	int			y;

	size = p.nom_size / (p.c * vec->z);
	inter.x = g->player.position.x + vec->x * size;
	inter.y = g->player.position.y + vec->y * size;
	inter.z = -p.d;
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (luminosity_px(g, t.color[y * t.size_line + x], inter));
}

static t_color	sort_color(t_color *color, int n)
{
	t_color	result;
	int		i;

	result = color[0];
	i = 0;
	while (++i < n)
	{
		if ((result.color == INVISIBLE_COLOR
				&& color[i].color != INVISIBLE_COLOR)
			|| (color[i].color != INVISIBLE_COLOR
				&& color[i].size < result.size))
			result = color[i];
	}
	return (result);
}

int	ft_pixel_color(t_game *game, t_vector *vec, t_sprite *sprite)
{
	t_color	color[3];
	t_color	result;

	color[0] = (t_color){-1, INVISIBLE_COLOR, (t_dot){0, 0, 0}};
	color[1] = (t_color){-1, INVISIBLE_COLOR, (t_dot){0, 0, 0}};
	color[2] = (t_color){-1, INVISIBLE_COLOR, (t_dot){0, 0, 0}};
	color[0].color = search_color_x(game, vec, &color[0]);
	color[1].color = search_color_y(game, vec, &color[1], color[0]);
	if (sprite && (color[0].size == -1
			|| sprite->dist_to_player <= color[0].size * color[0].size)
		&& (color[1].size == -1
			|| sprite->dist_to_player <= color[1].size * color[1].size))
		color[2].color = ft_search_sprite(game, vec,
				&color[2], game->player.view.sprites_in_fov);
	result = sort_color(color, 3);
	if (result.color == INVISIBLE_COLOR)
	{
		if (vec->z < 0)
			return (sky_ground_color(game, vec, game->sky_ground.ground_texture,
					game->sky_ground.ground_plane));
		else
			return (sky_ground_color(game, vec, game->sky_ground.sky_texture,
					game->sky_ground.sky_plane));
	}
	return (luminosity_px(game, result.color, result.inter));
}

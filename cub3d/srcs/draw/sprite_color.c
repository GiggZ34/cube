/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:32:18 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 18:33:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sprite_color(t_sprite *sprite, double x, double y)
{
	int			w;
	int			h;
	t_texture	*texture;

	if (x > sprite->width || y > sprite->height)
		return (INVISIBLE_COLOR);
	texture = sprite->tile_sheet;
	x /= sprite->width;
	y /= sprite->height;
	w = x * texture->width;
	h = texture->height - y * texture->height;
	return (texture->color[h * texture->size_line + w]);
}

static int	calculate_position(t_sprite *sprite, t_color *s)
{
	double		dist;
	t_vector	dir;

	dist = pow(sprite->frist_px.x - s->inter.x, 2)
		+ pow(sprite->frist_px.y - s->inter.y, 2);
	if (dist <= pow(sprite->width, 2))
	{
		dir.x = sprite->frist_px.x - s->inter.x;
		dir.y = sprite->frist_px.y - s->inter.y;
		if (dir.x * sprite->vec_write.x >= -PRECISION
			&& dir.y * sprite->vec_write.y >= -PRECISION)
			return (sprite_color(sprite, sqrt(dist), s->inter.z));
	}
	return (INVISIBLE_COLOR);
}

int	ft_search_sprite(t_game *g, t_vector *v, t_color *s, t_list *lst)
{
	t_sprite	*sprite;
	int			color;

	color = INVISIBLE_COLOR;
	while (lst && color == INVISIBLE_COLOR)
	{
		sprite = lst->content;
		s->size = sprite->plane.nom_size
			/ (sprite->plane.a * v->x + sprite->plane.b * v->y);
		s->inter.x = g->player.position.x + v->x * s->size;
		s->inter.y = g->player.position.y + v->y * s->size;
		s->inter.z = g->player.position.z + v->z * s->size;
		if (s->inter.z >= 0 && s->inter.z < sprite->height)
			color = calculate_position(sprite, s);
		lst = lst->next;
	}
	return (color);
}

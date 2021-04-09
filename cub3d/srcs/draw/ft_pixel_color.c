/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/08 17:16:23 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_in_wall(t_texture *texture, t_dot inter, char dir)
{
	int	x;
	int	y;

	y = texture->height - (texture->height * inter.z);
	if (dir == 'y')
		x = texture->width * (inter.x - floor(inter.x));
	else
		x = texture->width * (inter.y - floor(inter.y));
	return ((texture->color[y * texture->size_line + x]));
}

static double	ft_is_wall(t_game *game, t_plane *plane, t_vector *v, t_dot *dot)
{
	double	size;
	int		y;
	int		x;

	size = plane->nom_size / (plane->a * v->x + plane->b * v->y);
	dot->x = game->player.position.x + v->x * size;
	dot->y = game->player.position.y + v->y * size;
	dot->z = game->player.position.z + v->z * size;
	if (dot->z < 0 || dot->z > 1)
		return (-1);
	if (plane->a != 0)
		x = ft_abs(plane->d);
	else
		x = floor(ft_abs((*dot).x));
	if (plane->b != 0)
		y = ft_abs(plane->d);
	else
		y = floor(ft_abs((*dot).y));
	if (plane->a != 0 && v->x < 0)
		x--;
	if (plane->b != 0 && v->y < 0)
		y--;
	if (x >= 0 && y >= 0 && y < game->file.height_map
		&& x < (int)ft_strlen(game->file.map[y]) && game->file.map[y][x] == '1')
		return (size);
	return (-1);
}

static int	define_lst_planes(t_game *game, t_vector *vec, t_list ***tab, char dir)
{
	int	step;

	if (dir == 'x')
	{
		*tab = game->tab_planes.left;
		step = -1;
		if (vec->x > 0)
		{
			*tab = game->tab_planes.right;
			step = 1;
		}
	}
	else
	{
		*tab = game->tab_planes.top;
		step = -1;
		if (vec->y > 0)
		{
			*tab = game->tab_planes.bottom;
			step = 1;
		}
	}
	return (step);
}

static int	ft_search_color_x(t_game *game, t_vector *vec, t_color *x)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		i;
	int		step;

	if (vec->x == 0 || game->player.position.x <= 0
		|| game->player.position.x > game->file.width_map - 1)
		return (INVISIBLE_COLOR);
	step = define_lst_planes(game, vec, &tab, 'x');
	i = floor(game->player.position.x) + step;
	lst = NULL;
	while (!lst && i >= 0 && i < game->file.width_map)
	{
		lst = tab[i];
		i += step;
	}
	while (lst)
	{
		plane = lst->content;
		if ((x->size = ft_is_wall(game, plane, vec, &x->inter)) != -1)
			return (ft_is_in_wall(plane->add, x->inter, 'x'));
		if (x->inter.z < 0 || x->inter.z > 1 || x->inter.x < 0 || x->inter.x >= game->file.width_map || x->inter.y < 0 || x->inter.y >= game->file.height_map)
			return (INVISIBLE_COLOR);
		lst = lst->next;
	}
	return (INVISIBLE_COLOR);
}

static int		ft_search_color_y(t_game *game, t_vector *vec, t_color *y, t_color x)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		i;
	int		step;

	if (vec->y == 0)
		return (INVISIBLE_COLOR);
	step = define_lst_planes(game, vec, &tab, 'y');
	i = floor(game->player.position.y + step);
	lst = NULL;
	while (!lst && i >= 0 && i < game->file.height_map)
	{
		lst = tab[i];
		i += step;
	}
	while (lst && (x.color == INVISIBLE_COLOR || y->size < x.size))
	{
		plane = lst->content;
		y->size = ft_is_wall(game, plane, vec, &y->inter);
		if (y->size != -1)
			return (ft_is_in_wall(plane->add, y->inter, 'y'));
		if (y->inter.z < 0 || y->inter.z > 1
			|| y->inter.x < 0 || y->inter.x >= game->file.width_map
			|| y->inter.y < 0 || y->inter.y >= game->file.height_map)
			return (INVISIBLE_COLOR);
		lst = lst->next;
	}
	return (INVISIBLE_COLOR);
}

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

static int	ft_search_sprites(t_game *g, t_vector *v, t_color *s, t_list *lst)
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

static int	sky_ground_color(t_game *game, t_vector *vec, t_texture t, t_plane p)
{
	double		size;
	t_dot		inter;
	int			x;
	int			y;

	size = p.nom_size / (p.c * vec->z);
	inter.x = game->player.position.x + vec->x * size;
	inter.y = game->player.position.y + vec->y * size;
	inter.z = -p.d;
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (luminosity_px(game, t.color[y * t.size_line + x], inter));
}

t_color	sort_color(t_color *color, int n)
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
	color[0].color = ft_search_color_x(game, vec, &color[0]);
	color[1].color = ft_search_color_y(game, vec, &color[1], color[0]);
	if (sprite && (color[0].size == -1
			|| sprite->dist_to_player <= color[0].size * color[0].size)
		&& (color[1].size == -1
			|| sprite->dist_to_player <= color[1].size * color[1].size))
		color[2].color = ft_search_sprites(game, vec,
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

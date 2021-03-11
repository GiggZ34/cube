/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 00:59:30 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_is_in_wall(t_texture *texture, t_dot inter, char dir)
{
	int			x;
	int			y;

	y = texture->height * inter.z;
	if (dir == 'y')
		x = texture->width * (inter.x - floor(inter.x));
	else
		x = texture->width * (inter.y - floor(inter.y));
	return (texture->color[y * texture->size_line + x]);
}

static double	ft_is_wall(t_game *game, t_plane *plane, t_vector v, t_dot *dot, char dir)
{
	t_dot	pos;
	char	**map;
	double	size;
	int		y;
	int		x;

	map = game->file->map;
	pos = game->player->position;
	size = ft_size_vec_plane(plane, v, pos);
	*dot = ft_intersect_plane_dot(pos, v, size);
	if ((*dot).z < 0 || (*dot).z > 1)
		return (-1);
	y = plane->b != 0 ? ft_abs(plane->d) : floor(ft_abs((*dot).y));
	x = plane->a != 0 ? ft_abs(plane->d) : floor(ft_abs((*dot).x));
	if (dir == 'x' && v.x < 0)
		x--;
	if (dir == 'y' && v.y < 0)
		y--;
	if (x >= 0 && y >= 0 && y < game->file->height_map
						&& x < (int)ft_strlen(map[y]) && map[y][x] == '1')
		return (size);
	return (-1);
}

static int		ft_search_color_x(t_game *game, t_vector vec, double *size)
{
	t_list	*lst;
	t_plane	*plane;
	t_dot	inter;
	t_list	**tab;
	int		i;
	int		step;

	if (vec.x == 0 || game->player->position.x < 0 || game->player->position.x >= game->file->width_map)
		return (-1);
	tab = game->tab_planes.left;
	step = -1;
	if (vec.x > 0)
	{
		tab = game->tab_planes.right;
		step = 1;
	}
	i = floor(game->player->position.x) + step;
	while (!(lst = tab[i]))
		i += step;
	while (lst)
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter, 'x')) != -1)
			return (ft_is_in_wall(plane->add, inter, 'x'));
		lst = lst->next;
	}
	return (-1);
}

static int		ft_search_color_y(t_game *game, t_vector vec, double *size)
{
	t_list	*lst;
	t_plane	*plane;
	t_dot	inter;
	t_list	**tab;
	int		i;
	int		step;

	step = 0;
	if (vec.y == 0 || game->player->position.y < 0 || game->player->position.y >= game->file->height_map)
		return (-1);
	tab = game->tab_planes.top;
	step = -1;
	if (vec.y > 0)
	{
		tab = game->tab_planes.bottom;
		step = 1;
	}
	i = floor(game->player->position.y + step);
	while (!(lst = tab[i]))
		i += step;
	while (lst)
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter, 'y')) != -1)
			return (ft_is_in_wall(plane->add, inter, 'y'));
		lst = lst->next;
	}
	return (-1);
}

static int	ft_search_sprite_color(t_sprite *sprite, t_texture *texture, double x, double y)
{
	int	w;
	int	h;

	x /= sprite->width;
	y = 1 - y / sprite->height;
	w = x * texture->width;
	h = y * texture->height;
	return (texture->color[h * texture->size_line + w]);
}

static int	ft_search_sprites(t_game *game, t_vector vec, double *size, t_list *lst)
{
	t_dot		inter;
	t_sprite	*sprite;
	t_vector	dir;
	double		tmp_size;
	int			color;
	int			tmp_color;
	double		dist;

	*size = -1;
	color = -1;
	while (lst)
	{
		sprite = lst->content;
		tmp_size = ft_size_vec_plane(&sprite->plane, vec, game->player->position);
		inter = ft_intersect_plane_dot(game->player->position, vec, tmp_size);
		dist = pow(sprite->frist_px.x - inter.x, 2) + pow(sprite->frist_px.y - inter.y, 2);
		if (((*size < 0 && tmp_size > 0) || (*size > tmp_size && tmp_size > 0))
			&& (dist <= pow(sprite->width, 2))
			&& inter.z >= 1 - sprite->height && inter.z <= 1)
		{
			dir.x = sprite->frist_px.x - inter.x;
			dir.y = sprite->frist_px.y - inter.y;
			if (dir.x * sprite->vec_write.x >= 0 && dir.y * sprite->vec_write.y >= 0 && (tmp_color = ft_search_sprite_color(sprite, sprite->tile_sheet, sqrt(dist), 1 - inter.z)) >= 0)
			{
				*size = tmp_size;
				color = tmp_color;
			}
		}
		lst = lst->next;
	}
	return (color);
}

int			ft_pixel_color(t_game *game, t_vector vec)
{
	double	size_x;
	double	size_y;
	double	size_s;
	int		color_x;
	int		color_y;
	int		color_sprite;

	size_x = 0;
	color_sprite = ft_search_sprites(game, vec, &size_s, game->player->view.sprites_in_fov);
	color_x = ft_search_color_x(game, vec, &size_x);
	color_y = ft_search_color_y(game, vec, &size_y);
	if (color_sprite < 0 && color_x < 0 && color_y < 0)
	{
		if (vec.z > 0)
			return (game->file->ground_color);
		else
			return (game->file->sky_color);
	}
	else if (color_sprite >= 0 && color_x < 0 && color_y < 0)
		return (color_sprite);
	else if (color_y >= 0 && color_x < 0 && color_sprite < 0)
		return (color_y);
	else if (color_x >= 0 && color_y < 0 && color_sprite < 0)
		return (color_x);
	else
	{
		if (color_sprite >= 0 && size_s > 0 && (size_s < size_x || size_x < 0) && (size_s < size_y || size_y < 0))
			return (color_sprite);
		else if (size_x > 0 && (size_x < size_y || size_y < 0))
			return (color_x);
		else
			return (color_y);
	}
}

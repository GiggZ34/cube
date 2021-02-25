/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/16 16:46:19 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_is_in_wall(t_plane *plane, t_dot inter, char dir)
{
	t_texture	*texture;
	int			x;
	int			y;

	texture = plane->add;
	y =  texture->height * inter.z;
	if (dir == 'y')
		x = texture->size_line * (inter.x - (int)inter.x);
	else
		x = texture->size_line * (inter.y - (int)inter.y);
	return (texture->color[y][x]);
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
	y = (int)ft_abs((*dot).y);
	x = (int)ft_abs((*dot).x);
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

	if (vec.x == 0)
		return (-1);
	tab = game->tab_planes.left;
	step = -1;
	if (vec.x > 0)
	{
		tab = game->tab_planes.right;
		step = 1;
	}
	i = (int)game->player->position.x + step;
	while (i >= 0 && i < game->file->width_map && !(lst = tab[i]))
		i += step;
	while (lst)
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter, 'x')) != -1)
			return (ft_is_in_wall(plane, inter, 'x'));
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
	if (vec.y == 0)
		return (-1);
	tab = game->tab_planes.top;
	step = -1;
	if (vec.y > 0)
	{
		tab = game->tab_planes.bottom;
		step = 1;
	}
	i = game->player->position.y + step;
	while (i >= 0 && i < game->file->height_map && !(lst = tab[i]))
		i += step;
	while (lst)
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter, 'y')) != -1)
			return (ft_is_in_wall(plane, inter, 'y'));
		lst = lst->next;
	}
	return (-1);
}

static int	ft_search_sprite_color(t_sprite *sprite, t_texture *texture, double x, double y, char dir)
{
	int	w;
	int	h;

	if (dir == 'L')
		w = texture->size_line / 2 - (x / sprite->width * texture->size_line);
	else
		w = texture->size_line / 2 + (x / sprite->width * texture->size_line);
	h = y * texture->height;
	return (texture->color[h][w]);
}

static int	ft_search_sprites(t_game *game, t_vector vec, double *size)
{
	t_list		*lst;
	t_dot		inter;
	t_sprite	*sprite;
	double		tmp_size;
	int			color;

	lst = game->lst_sprites;
	*size = -1;
	color = -1;
	while (lst)
	{
		sprite = lst->content;
		tmp_size = ft_size_vec_plane(&sprite->plane, vec, game->player->position);
		inter = ft_intersect_plane_dot(game->player->position, vec, tmp_size);
		if ((*size < 0 || *size > tmp_size)
			&& inter.x >= sprite->position.x - sprite->width / 2 && inter.x <= sprite->position.x + sprite->width / 2
			&& inter.y >= sprite->position.y - sprite->width / 2 && inter.y <= sprite->position.y + sprite->width / 2
			&& sqrt(pow(sprite->position.x - inter.x, 2) + pow(sprite->position.y - inter.y, 2)) <= sprite->width / 2
			&& inter.z >= 0 && inter.z <= sprite->height)
		{
			*size = tmp_size;
			if (inter.x >= sprite->position.x - sprite->width / 2 && inter.x <= sprite->position.x + sprite->width / 2)
				color = ft_search_sprite_color(sprite, sprite->tile_sheet, sqrt(pow(sprite->position.x - inter.x, 2) + pow(sprite->position.y - inter.y, 2)), inter.z, 'L');
			else
				color = ft_search_sprite_color(sprite, sprite->tile_sheet, sqrt(pow(sprite->position.x - inter.x, 2) + pow(sprite->position.y - inter.y, 2)), inter.z, 'R');
		}
		lst = lst->next;
	}
	if (*size < 0)
		return (-1);
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

	color_sprite = ft_search_sprites(game, vec, &size_s);
	color_x = ft_search_color_x(game, vec, &size_x);
	color_y = ft_search_color_y(game, vec, &size_y);
	if (color_sprite < 0 && color_x < 0 && color_y < 0)
	{
		if (vec.z > 0)
			return (game->file->ground_color);
		else
			return (game->file->sky_color);
	}
	else if (color_sprite > 0 && color_x == -1 && color_y == -1)
		return (color_sprite);
	else if (color_y != -1 && color_x == -1 && color_sprite < 0)
		return (color_y);
	else if (color_x != -1 && color_y == -1 && color_sprite < 0)
		return (color_x);
	else
	{
		if (color_sprite > 0 && size_s > 0 && (size_s < size_x || size_x < 0) && (size_s < size_y || size_y < 0))
			return (color_sprite);
		else if (color_x > 0 && size_x > 0 && (size_x < size_y || size_y < 0))
			return (color_x);
		else
			return (color_y);
	}
}

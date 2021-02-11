/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/10 14:05:17 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_is_in_wall(t_plane *plane, t_dot inter, char dir)
{
	t_texture	*texture;
	double		x;
	double		y;

	texture = plane->add;
	y = texture->height * (inter.z - (int)inter.z);
	if (dir == 'y')
		x = texture->width * (inter.x - (int)inter.x);
	else
		x = texture->width * (inter.y - (int)inter.y);
	return (texture->color[(int)y][(int)x]);
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
/*/
static int	ft_search_sprite_color(t_texture *texture, double x, double y)
{
	int	w;
	int	h;

	w = x * texture->width;
	h = y * texture->height;
	return (texture->color[h][w]);
}
/*/
static int	ft_search_sprites(t_game *game, t_vector vec, double *size)
{
	t_list		*lst;
	t_dot		inter;
	t_dot		pos;
	t_plane		*plane;
	t_sprite	*sprite;
	double		tmp_size;
	int			color;

	lst = game->lst_planes_sprites;
	pos = game->player->position;
	*size = -1;
	color = -1;
	while (lst)
	{
		plane = lst->content;
		sprite = plane->add;
		tmp_size = ft_size_vec_plane(plane, vec, pos);
		inter = ft_intersect_plane_dot(pos, vec, tmp_size);
	//	printf("%d __ inter.x [ %.f ] | inter.y [ %.f ] | inter.z [ %.f ]\n",ft_lstsize(game->lst_sprites) - ft_lstsize(lst) + 1, inter.x, inter.y, inter.z);
		if ((*size < 0 || *size > tmp_size)
			&& inter.x >= sprite->position.x - 0.25 && inter.x <= sprite->position.x + 0.25
			&& inter.y >= sprite->position.y - 0.25 && inter.y <= sprite->position.y + 0.25
			&& inter.z >= 0 && inter.z <= 0.5)
		{
			*size = tmp_size;
			color = 255;//ft_search_sprite_color(sprite->tile_sheet, sqrt(pow(sprite->position.x - inter.x, 2) + pow(sprite->position.y - inter.y, 2)), inter.z);
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

	color_sprite = ft_search_sprites(game, vec, &size_s);
	color_x = ft_search_color_x(game, vec, &size_x);
	color_y = ft_search_color_y(game, vec, &size_y);
	if (color_sprite == -1 && color_x == -1 && color_y == -1)
	{
		if (vec.z > 0)
			return (game->file->ground_color);
		else
			return (game->file->sky_color);
	}
	if (color_sprite == -1 && color_x == -1)
		return (color_y);
	else if (color_sprite == -1 && color_y == -1)
		return (color_x);
	else
	{
		if (color_sprite > -1 && size_s < size_x && size_s < size_y)
			return (color_sprite);
		else if (size_x > -1 && size_x < size_y)
			return (color_x);
		else
			return (color_y);
	}
	return (0);
}

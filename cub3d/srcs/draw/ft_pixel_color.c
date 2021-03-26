/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/25 16:28:38 by grivalan         ###   ########lyon.fr   */
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

static double	ft_is_wall(t_game *game, t_plane *plane, t_vector v, t_dot *dot)
{
	t_dot	pos;
	char	**map;
	double	size;
	int		y;
	int		x;

	map = game->file.map;
	pos = game->player.position;
	size = ft_size_vec_plane(plane, v, pos);
	*dot = ft_intersect_plane_dot(pos, v, size);
	if ((*dot).z < 0 || (*dot).z > 1)
		return (-1);
	y = plane->b != 0 ? ft_abs(plane->d) : floor(ft_abs((*dot).y));
	x = plane->a != 0 ? ft_abs(plane->d) : floor(ft_abs((*dot).x));
	if (plane->a != 0 && v.x < 0)
		x--;
	if (plane->b != 0 && v.y < 0)
		y--;
	if (x >= 0 && y >= 0 && y < game->file.height_map
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

	if (vec.x == 0 || game->player.position.x <= 0 || game->player.position.x > game->file.width_map - 1)
		return (UNVISIBLE_COLOR);
	tab = game->tab_planes.left;
	step = -1;
	if (vec.x > 0)
	{
		tab = game->tab_planes.right;
		step = 1;
	}
	i = floor(game->player.position.x) + step;
	while (i >= 0 && i < game->file.width_map && !(lst = tab[i]))
		i += step;
	while (lst)
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter)) != -1)
			return (ft_is_in_wall(plane->add, inter, 'x'));
		if (inter.z < 0 || inter.z > 1 || inter.x < 0 || inter.x >= game->file.width_map || inter.y < 0 || inter.y >= game->file.height_map)
			return (UNVISIBLE_COLOR);
		lst = lst->next;
	}
	return (UNVISIBLE_COLOR);
}

static int		ft_search_color_y(t_game *game, t_vector vec, double *size, t_color x)
{
	t_list	*lst;
	t_plane	*plane;
	t_dot	inter;
	t_list	**tab;
	int		i;
	int		step;

	step = 0;
	if (vec.y == 0 || game->player.position.y <= 0 || game->player.position.y > game->file.height_map - 1)
		return (UNVISIBLE_COLOR);
	tab = game->tab_planes.top;
	step = -1;
	if (vec.y > 0)
	{
		tab = game->tab_planes.bottom;
		step = 1;
	}
	i = floor(game->player.position.y + step);
	while (i >= 0 && i < game->file.height_map && !(lst = tab[i]))
		i += step;
	while (lst && (x.color == UNVISIBLE_COLOR || *size < x.size))
	{
		plane = lst->content;
		if ((*size = ft_is_wall(game, plane, vec, &inter)) != -1)
			return (ft_is_in_wall(plane->add, inter, 'y'));
		if (inter.z < 0 || inter.z > 1 || inter.x < 0 || inter.x >= game->file.width_map || inter.y < 0 || inter.y >= game->file.height_map)
			return (UNVISIBLE_COLOR);
		lst = lst->next;
	}
	return (UNVISIBLE_COLOR);
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
	int			color;
	double		dist;

	*size = -1;
	color = UNVISIBLE_COLOR;
	while (lst)
	{
		sprite = lst->content;
		*size = ft_size_vec_plane(&sprite->plane, vec, game->player.position);
		inter = ft_intersect_plane_dot(game->player.position, vec, *size);
		if (inter.z > 1 - sprite->height && inter.z < 1)
		{
			dist = pow(sprite->frist_px.x - inter.x, 2) + pow(sprite->frist_px.y - inter.y, 2);
			if (dist <= sprite->width * sprite->width)
			{
				dir.x = sprite->frist_px.x - inter.x;
				dir.y = sprite->frist_px.y - inter.y;
				if (dir.x * sprite->vec_write.x >= 0 && dir.y * sprite->vec_write.y >= 0
				&& (color = ft_search_sprite_color(sprite, sprite->tile_sheet, sqrt(dist), 1 - inter.z)) != UNVISIBLE_COLOR)
					return (color);
			}
		}
		else
			return (UNVISIBLE_COLOR);
		lst = lst->next;
	}
	return (UNVISIBLE_COLOR);
}

int			ft_sky_color(t_game *game, t_vector vec)
{
	double	size;
	t_dot	inter;
	t_texture t;
	int		x;
	int		y;

	t = game->sky_ground.sky_texture;
	size = ft_abs(ft_size_vec_plane(&game->sky_ground.sky_plane, vec, game->player.position));
	inter = ft_intersect_plane_dot(game->player.position, vec, size);
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (t.color[y * t.size_line + x]);

}

int			ft_ground_color(t_game *game, t_vector vec)
{
	double	size;
	t_dot	inter;
	t_texture t;
	int		x;
	int		y;

	t = game->sky_ground.ground_texture;
	size = ft_abs(ft_size_vec_plane(&game->sky_ground.ground_plane, vec, game->player.position));
	inter = ft_intersect_plane_dot(game->player.position, vec, size);
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (t.color[y * t.size_line + x]);

}

int			ft_pixel_color(t_game *game, t_vector vec, t_sprite *sprite)
{
	t_color	x;
	t_color	y;
	t_color	s;

	x = (t_color){-1, UNVISIBLE_COLOR, '\0'};
	y = (t_color){-1, UNVISIBLE_COLOR, '\0'};
	s = (t_color){-1, UNVISIBLE_COLOR, '\0'};

	x.color = ft_search_color_x(game, vec, &x.size);
	y.color = ft_search_color_y(game, vec, &y.size, x);
	if (sprite && (x.size == -1 || sprite->dist_to_player <= pow(x.size, 2)) && (y.size == -1 || sprite->dist_to_player <= pow(y.size, 2)))
		s.color = ft_search_sprites(game, vec, &s.size, game->player.view.sprites_in_fov);
	if (s.color < 0 && x.color < 0 && y.color < 0)
	{
		if (vec.z > 0)
			return (game->file.ground_color);//ft_ground_color(game, vec));
		else
			return (game->file.sky_color);//ft_sky_color(game, vec));
	}
	else if (s.color >= 0 && x.color < 0 && y.color < 0)
		return (s.color);
	else if (y.color >= 0 && x.color < 0 && s.color < 0)
		return (y.color);
	else if (x.color >= 0 && y.color < 0 && s.color < 0)
		return (x.color);
	else
	{
		if (s.color >= 0 && s.size > 0 && (s.size < x.size || x.size < 0) && (s.size < y.size || y.size < 0))
			return (s.color);
		else if (x.size > 0 && (x.size < y.size || y.size < 0))
			return (x.color);
		else
			return (y.color);
	}
}

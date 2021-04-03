/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/03 16:03:22 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			shadow_px(int color, double size)
{
	unsigned char	rgb[3];
	int				i;

	if (color == UNVISIBLE_COLOR)
		return (UNVISIBLE_COLOR);
	i = -1;
	while (++i < 3)
		rgb[i] = (unsigned char)(color >> (i * 8));
	size = size / DIST_MAX;
	if (size > 1)
		size = 1;
	i = -1;
	while (++i < 3)
		rgb[i] *= 1 - size;
	return (ft_color_generate(rgb[2], rgb[1], rgb[0], 0));
}

static int		ft_is_in_wall(t_texture *texture, t_dot inter, char dir, double size)
{
	int			x;
	int			y;

	y = texture->height - (texture->height * inter.z);
	if (dir == 'y')
		x = texture->width * (inter.x - floor(inter.x));
	else
		x = texture->width * (inter.y - floor(inter.y));
	return (shadow_px((texture->color[y * texture->size_line + x]), size));
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
	size = ft_size_vec_plane(plane, v);
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
			return (ft_is_in_wall(plane->add, inter, 'x', *size));
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
			return (ft_is_in_wall(plane->add, inter, 'y', *size));
		if (inter.z < 0 || inter.z > 1 || inter.x < 0 || inter.x >= game->file.width_map || inter.y < 0 || inter.y >= game->file.height_map)
			return (UNVISIBLE_COLOR);
		lst = lst->next;
	}
	return (UNVISIBLE_COLOR);
}

static int	ft_search_sprite_color(t_sprite *sprite, double x, double y)
{
	int			w;
	int			h;
	t_texture	*texture;

	if (x > sprite->width || y > sprite->height)
		return (UNVISIBLE_COLOR);
	texture = sprite->tile_sheet;
	x /= sprite->width;
	y /= sprite->height;
	w = x * texture->width;
	h = texture->height - y * texture->height;
	return (texture->color[h * texture->size_line + w]);
}

static int	red_color(int color, int size)
{
	unsigned char	rgb[3];

	rgb[0] = (unsigned char)(color);
	rgb[1] = (unsigned char)(color >> 8);
	rgb[2] = (unsigned char)(color >> 16);
	if ((int)rgb[2] >= 253 && (int)rgb[1] <= 3 && (int)rgb[0] >= 164 && (int)rgb[0] <= 167)
		return (ft_color_generate(190, 24, 24, 0));
	return (shadow_px(color, size));
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
	while (lst && color == UNVISIBLE_COLOR)
	{
		sprite = lst->content;
		*size = ft_size_vec_plane(&sprite->plane, vec);
		inter = ft_intersect_plane_dot(game->player.position, vec, *size);
		if (inter.z >= 0 && inter.z < sprite->height)
		{
			dist = pow(sprite->frist_px.x - inter.x, 2) + pow(sprite->frist_px.y - inter.y, 2);
			if (dist <= pow(sprite->width, 2))
			{
				dir.x = sprite->frist_px.x - inter.x;
				dir.y = sprite->frist_px.y - inter.y;
				if (dir.x * sprite->vec_write.x >= -0.00001 && dir.y * sprite->vec_write.y >= -0.00001)
					color = ft_search_sprite_color(sprite, sqrt(dist), inter.z);
			}
		}
		lst = lst->next;
	}
	return (red_color(color, *size));
}

int			ft_sky_color(t_game *game, t_vector vec)
{
	double	size;
	t_dot	inter;
	t_texture t;
	int		x;
	int		y;

	t = game->sky_ground.sky_texture;
	size = ft_abs(ft_size_vec_plane(&game->sky_ground.sky_plane, vec));
	inter = ft_intersect_plane_dot(game->player.position, vec, size);
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (shadow_px(t.color[y * t.size_line + x], size));

}

int			ft_ground_color(t_game *game, t_vector vec)
{
	double	size;
	t_dot	inter;
	t_texture t;
	int		x;
	int		y;

	t = game->sky_ground.ground_texture;
	size = ft_abs(ft_size_vec_plane(&game->sky_ground.ground_plane, vec));
	inter = ft_intersect_plane_dot(game->player.position, vec, size);
	y = t.height * (inter.y - floor(inter.y));
	x = t.width * (inter.x - floor(inter.x));
	return (shadow_px(t.color[y * t.size_line + x], size));

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
	if (sprite && (x.size == -1 || sprite->dist_to_player <= x.size * x.size) && (y.size == -1 || sprite->dist_to_player <= y.size * y.size))
		s.color = ft_search_sprites(game, vec, &s.size, game->player.view.sprites_in_fov);
	if (s.color < 0 && x.color < 0 && y.color < 0)
	{
		if (vec.z < 0)
			return (ft_ground_color(game, vec));
		else
			return (ft_sky_color(game, vec));
	}
	else if (s.color != UNVISIBLE_COLOR && x.color == UNVISIBLE_COLOR && y.color == UNVISIBLE_COLOR)
		return (s.color);
	else if (y.color != UNVISIBLE_COLOR && x.color == UNVISIBLE_COLOR && s.color == UNVISIBLE_COLOR)
		return (y.color);
	else if (x.color != UNVISIBLE_COLOR && y.color == UNVISIBLE_COLOR && s.color == UNVISIBLE_COLOR)
		return (x.color);
	else
	{
		if (s.color != UNVISIBLE_COLOR && s.size > 0 && (s.size < x.size || x.size < 0) && (s.size < y.size || y.size < 0))
			return (s.color);
		else if (x.size > 0 && (x.size < y.size || y.size < 0))
			return (x.color);
		else
			return (y.color);
	}
}

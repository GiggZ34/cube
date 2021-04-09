/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/09 12:07:34 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	is_wall(t_game *game, t_plane *p, t_vector *v, t_dot pos)
{
	char	**map;
	float	size;
	int		y;
	int		x;
	t_dot	dot;

	map = game->file.map;
	size = -(p->a * pos.x + p->b * pos.y + p->d) / (p->a * v->x + p->b * v->y);
	dot.x = pos.x + v->x * size;
	dot.y = pos.y + v->y * size;
	y = ft_int_ternary(p->b != 0, ft_abs(p->d), floor(ft_abs(dot.y)));
	x = ft_int_ternary(p->a != 0, ft_abs(p->d), floor(ft_abs(dot.x)));
	if (p->a != 0 && v->x < 0)
		x--;
	if (p->b != 0 && v->y < 0)
		y--;
	if (x >= 0 && y >= 0 && y < game->file.height_map
		&& x < (int)ft_strlen(map[y]) && map[y][x] == '1')
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

static int	search_collide_x(t_game *game, t_vector *vec, t_light pos)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		i;
	int		step;
	float	size;

	size = -1;
	lst = NULL;
	if (!vec->x)
		return (0);
	step = define_lst_planes(game, vec, &tab, 'x');
	i = floor(pos.x);
	while (i >= 0 && i < game->file.width_map && !lst)
	{
		lst = tab[i];
		i += step;
	}
	while (lst && size == -1)
	{
		plane = lst->content;
		size = is_wall(game, plane, vec,
				(t_dot){pos.x, pos.y, pos.z});
		lst = lst->next;
	}
	if (size >= 0 && size < 1 - PRECISION)
		return (1);
	return (0);
}

static int	search_collide_y(t_game *game, t_vector *vec, t_light pos)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		i;
	int		step;
	float	size;

	lst = NULL;
	size = -1;
	if (!vec->y)
		return (0);
	step = define_lst_planes(game, vec, &tab, 'y');
	i = floor(pos.y);
	while (i >= 0 && i < game->file.height_map && !lst)
	{
		lst = tab[i];
		i += step;
	}
	while (lst && size == -1)
	{
		plane = lst->content;
		size = is_wall(game, plane, vec,
				(t_dot){pos.x, pos.y, pos.z});
		lst = lst->next;
	}
	if (size >= 0 && size < 1 - PRECISION)
		return (1);
	return (0);
}

static void	ft_ratio_color(float *rgb)
{
	float	max;
	float	ratio;
	int		i;

	i = -1;
	max = 0;
	ratio = 1;
	while (++i < 3)
	{
		if (rgb[i] > max)
			max = rgb[i];
	}
	if (max > 255)
	{
		ratio = 255 / max;
		i = -1;
		while (++i < 3)
			rgb[i] *= ratio;
	}
}

int	luminosity_px(t_game *game, int color, t_dot collide)
{
	float		rgb[3];
	float		rgb_tmp[3];
	int			i;
	double		size;
	t_vector	to_px;
	t_light		*light;

	rgb_tmp[0] = 0;
	rgb_tmp[1] = 0;
	rgb_tmp[2] = 0;
	if (!game->debug)
		return (color);
	if (color == INVISIBLE_COLOR)
		return (INVISIBLE_COLOR);
	i = -1;
	while (++i < 3)
		rgb[i] = ((unsigned char)(color >> (i * 8))) * 0.00392156862;
	light = game->light;
	while (light)
	{
		to_px.x = collide.x - light->x;
		to_px.y = collide.y - light->y;
		to_px.z = collide.z - light->z;
		size = (to_px.x * to_px.x + to_px.y * to_px.y + to_px.z * to_px.z) * 0.25;
		if (size < 15 && !search_collide_y(game, &to_px, *light) && !search_collide_x(game, &to_px, *light))
		{
			i = -1;
			while (++i < 3)
				rgb_tmp[i] += light->rgb[i] / size;
			ft_ratio_color(rgb_tmp);
		}
		light = light->next;
	}
	i = -1;
	while (++i < 3)
		rgb[i] *= rgb_tmp[i];
	return (ft_color_generate((unsigned char)rgb[2], (unsigned char)rgb[1], (unsigned char)rgb[0], 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:10:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/23 18:06:20 by grivalan         ###   ########lyon.fr   */
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

static int	search_collide_x(t_game *game, t_vector *vec, t_light pos)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		step;
	float	size;

	size = -1;
	lst = NULL;
	if (!vec->x)
		return (0);
	step = define_lst_planes(game, vec, &tab, 'x');
	lst = search_list(tab, pos.x, step, game->file.width_map);
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
	int		step;
	float	size;

	lst = NULL;
	size = -1;
	if (!vec->y)
		return (0);
	step = define_lst_planes(game, vec, &tab, 'y');
	lst = search_list(tab, pos.y, step, game->file.height_map);
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

void	check_light(t_game *game, t_dot collide, float *rgb)
{
	t_light		*light;
	t_vector	to_px;
	double		size;
	int			i;

	light = game->light;
	while (light)
	{
		to_px.x = collide.x - light->x;
		to_px.y = collide.y - light->y;
		to_px.z = collide.z - light->z;
		size = (to_px.x * to_px.x + to_px.y * to_px.y + to_px.z * to_px.z)
			* 0.25;
		if (size < 15 && !search_collide_y(game, &to_px, *light)
			&& !search_collide_x(game, &to_px, *light))
		{
			i = -1;
			while (++i < 3)
				rgb[i + 3] += light->rgb[i] * 255 / size * DIST_MAX;
			ft_ratio_color(&(rgb[3]));
		}
		light = light->next;
	}
}

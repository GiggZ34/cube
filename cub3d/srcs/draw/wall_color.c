/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:54:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/23 15:47:54 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	define_lst_planes(t_game *g, t_vector *vec, t_list ***tab, char dir)
{
	int	step;

	if (dir == 'x')
	{
		*tab = g->tab_planes.left;
		step = -1;
		if (vec->x > 0)
		{
			*tab = g->tab_planes.right;
			step = 1;
		}
	}
	else
	{
		*tab = g->tab_planes.top;
		step = -1;
		if (vec->y > 0)
		{
			*tab = g->tab_planes.bottom;
			step = 1;
		}
	}
	return (step);
}

t_list	*search_list(t_list **lst, int pos, int step, int max)
{
	t_list	*result;

	result = NULL;
	pos += step;
	while (!result && pos >= 0 && pos < max)
	{
		result = lst[pos];
		pos += step;
	}
	return (result);
}

int	search_color_x(t_game *g, t_vector *vec, t_color *x)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		step;

	if (vec->x == 0 || g->player.position.x <= 0
		|| g->player.position.x > g->file.width_map - 1)
		return (INVISIBLE_COLOR);
	step = define_lst_planes(g, vec, &tab, 'x');
	lst = search_list(tab, g->player.position.x, step, g->file.width_map);
	while (lst)
	{
		plane = lst->content;
		x->size = ft_is_wall(g, plane, vec, &x->inter);
		if ((x->size) != -1)
			return (ft_is_in_wall(plane->add, x->inter, 'x'));
		if (x->inter.z < 0 || x->inter.z > 1 || x->inter.x < 0
			|| x->inter.x >= g->file.width_map || x->inter.y < 0
			|| x->inter.y >= g->file.height_map)
			return (INVISIBLE_COLOR);
		lst = lst->next;
	}
	return (INVISIBLE_COLOR);
}

int	search_color_y(t_game *g, t_vector *vec, t_color *y, t_color x)
{
	t_list	*lst;
	t_plane	*plane;
	t_list	**tab;
	int		step;

	if (vec->y == 0)
		return (INVISIBLE_COLOR);
	step = define_lst_planes(g, vec, &tab, 'y');
	lst = search_list(tab, g->player.position.y, step, g->file.height_map);
	while (lst && (x.color == INVISIBLE_COLOR || y->size < x.size))
	{
		plane = lst->content;
		y->size = ft_is_wall(g, plane, vec, &y->inter);
		if (y->size != -1)
			return (ft_is_in_wall(plane->add, y->inter, 'y'));
		if (y->inter.z < 0 || y->inter.z > 1
			|| y->inter.x < 0 || y->inter.x >= g->file.width_map
			|| y->inter.y < 0 || y->inter.y >= g->file.height_map)
			return (INVISIBLE_COLOR);
		lst = lst->next;
	}
	return (INVISIBLE_COLOR);
}

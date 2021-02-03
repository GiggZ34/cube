/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:25:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 17:19:25 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall	*ft_init_wall(t_wall *wall, t_dot pos)
{
	t_wall *new_wall;

	if (!(new_wall = ft_calloc(sizeof(t_wall), 1)))
		return (NULL);
	new_wall->pos.x = pos.x;
	new_wall->pos.y = pos.y;
	new_wall->texture = wall->texture;
	new_wall->width = 0;
	new_wall->plane.a = wall->plane.a;
	new_wall->plane.b = wall->plane.b;
	new_wall->plane.c = wall->plane.c;
	new_wall->plane.d = wall->plane.d;
	return (new_wall);
}

static int		ft_create_h_wall(t_list **walls, t_wall *wall, t_dot p, int id)
{
	t_list	*lst;
	t_wall	*new_wall;
	int		i;

	if (!(new_wall = ft_init_wall(wall, p)))
		return (3);
	i = (int)p.x;
	while (id < wall->n_tab_size && wall->tab_size[id] == i)
	{
		i++;
		id++;
		new_wall->width++;
	}
	if (!(lst = ft_lstnew(new_wall)))
	{
		free(new_wall);
		return (3);
	}
	ft_lstadd_front(walls, lst);
	p.x = wall->tab_size[id];
	if (id < wall->n_tab_size)
		ft_create_h_wall(walls, wall, p, id);
	return (0);
}

static int		ft_create_v_wall(t_list **walls, t_wall *wall, t_dot p, int id)
{
	t_list	*lst;
	t_wall	*new_wall;
	int		i;

	if (!(new_wall = ft_init_wall(wall, p)))
		return (3);
	i = (int)p.y;
	while (id < wall->n_tab_size && wall->tab_size[id] == i)
	{
		i++;
		id++;
		new_wall->width++;
	}
	if (!(lst = ft_lstnew(new_wall)))
	{
		free(new_wall);
		return (3);
	}
	ft_lstadd_front(walls, lst);
	p.y = wall->tab_size[id];
	if (id < wall->n_tab_size)
		ft_create_v_wall(walls, wall, p, id);
	return (0);
}

static void		ft_del_wall(void *content)
{
	t_wall	*wall;

	wall = content;
	free(wall->tab_size);
	free(wall);
}

int				ft_create_walls(t_list **lst_walls)
{
	t_wall	*wall;
	t_list	*tmp;
	t_list	*current;
	t_dot	pos;

	current = *lst_walls;
	while (current)
	{
		wall = current->content;
		ft_sort_numbers(wall->tab_size, wall->n_tab_size);
		if (wall->plane.a == 1)
		{
			pos.x = -(wall->plane.d);
			pos.y = wall->tab_size[0];
			if ((ft_create_v_wall(lst_walls, wall, pos, 0)))
				return (3);
		}
		else if (wall->plane.b == 1)
		{
			pos.x = wall->tab_size[0];
			pos.y = -(wall->plane.d);
			if ((ft_create_h_wall(lst_walls, wall, pos, 0)))
				return (3);
		}
		tmp = current;
		current = current->next;
		ft_lstclearone(lst_walls, tmp, &(ft_del_wall));
	}
	return (0);
}

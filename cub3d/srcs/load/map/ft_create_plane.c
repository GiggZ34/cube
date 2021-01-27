/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:45:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 14:26:09 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			ft_in_struct(t_list *lst_planes, t_plane *current_plane)
{
	t_plane *plane;

	while (lst_planes)
	{
		plane = lst_planes->content;
		if (plane->a == current_plane->a && plane->b == current_plane->b
						&& plane->d == current_plane->d)
			return (1);
		lst_planes = lst_planes->next;
	}
	return (0);
}

static t_plane		*ft_init_plane(void)
{
	t_plane *plane;

	if (!(plane = ft_calloc(sizeof(t_plane), 1)))
		return (0);
	plane->a = 0;
	plane->b = 0;
	plane->c = 0;
	plane->d = 0;
	return (plane);
}

static int			ft_plane_to_list(t_game *game, t_plane *plane)
{
	t_list	*lst;

	if (ft_in_struct(game->lst_planes, plane) == 0)
	{
		if (!(lst = ft_lstnew(plane)))
			return (3);
		ft_lstadd_back(&(game->lst_planes), lst);
	}
	else
		free(plane);
	return (0);
}

int					ft_create_plane(t_game *game, int x, int y, char dir)
{
	t_plane		*plane;

	if (!(plane = ft_init_plane()))
		return (3);
	if (dir == 'V')
	{
		plane->a = 1;
		plane->d = -x;
	}
	else if (dir == 'H')
	{
		plane->b = 1;
		plane->d = -y;
	}
	if (ft_plane_to_list(game, plane))
		return (3);
	return (0);
}

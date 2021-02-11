/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:37:35 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/05 08:51:48 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_plane		*ft_search_plane_top(t_list *lst, int y)
{
	t_plane *plane;

	while (lst)
	{
		plane = lst->content;
		if (plane->b == 1 && plane->d == -y)
			return (plane);
		lst = lst->next;
	}
	return (NULL);
}

t_plane		*ft_search_plane_bottom(t_list *lst, int y)
{
	t_plane *plane;

	while (lst)
	{
		plane = lst->content;
		if (plane->b == -1 && plane->d == y)
			return (plane);
		lst = lst->next;
	}
	return (NULL);
}

t_plane		*ft_search_plane_right(t_list *lst, int x)
{
	t_plane *plane;

	while (lst)
	{
		plane = lst->content;
		if (plane->a == -1 && plane->d == x)
			return (plane);
		lst = lst->next;
	}
	return (NULL);
}

t_plane		*ft_search_plane_left(t_list *lst, int x)
{
	t_plane *plane;

	while (lst)
	{
		plane = lst->content;
		if (plane->a == 1 && plane->d == -x)
			return (plane);
		lst = lst->next;
	}
	return (NULL);
}

t_plane		*ft_search_plane(t_list *lst, int x, int y, char dir)
{
	if (dir == 'R')
		return (ft_search_plane_right(lst, x));
	else if (dir == 'L')
		return (ft_search_plane_left(lst, x));
	else if (dir == 'T')
		return (ft_search_plane_top(lst, y));
	else if (dir == 'B')
		return (ft_search_plane_bottom(lst, y));
	return (NULL);
}

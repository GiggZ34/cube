/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:45:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:47:09 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_plane	*ft_init_plane(t_game *game, int x, int y, char dir)
{
	t_plane	*plane;

	if (!(plane = ft_calloc(sizeof(t_plane), 1)))
		return (NULL);
	plane->a = 0;
	plane->b = 0;
	plane->c = 0;
	if (dir == 'L')
	{
		plane->a = 1;
		plane->d = -x;
		plane->add = game->file.texture_we;
	}
	else if (dir == 'R')
	{
		plane->a = -1;
		plane->d = x;
		plane->add = game->file.texture_ea;
	}
	else if (dir == 'T')
	{
		plane->b = 1;
		plane->d = -y;
		plane->add = game->file.texture_no;
	}
	else if (dir == 'B')
	{
		plane->b = -1;
		plane->d = y;
		plane->add = game->file.texture_so;
	}
	return (plane);
}

static int		ft_plane_to_list(t_game *game, t_list **lst, t_plane *plane)
{
	t_list	*new_lst;

	if (!(new_lst = ft_lstnew(plane)))
	{
		free(plane);
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	}
	ft_lstadd_back(lst, new_lst);
	return (0);
}

int				ft_create_plane(t_game *game, t_list **lst, int *pos, char dir)
{
	t_plane	*plane;

	if (!(plane = ft_search_plane(*lst, pos[0], pos[1], dir)))
	{
		if (!(plane = ft_init_plane(game, pos[0], pos[1], dir)))
			return (ft_trash_game(game, allocation_fail, -1, "\n"));
		ft_plane_to_list(game, lst, plane);
		ft_sort_planes(*lst);
	}
	return (0);
}

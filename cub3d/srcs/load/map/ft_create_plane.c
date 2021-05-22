/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:45:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 15:32:05 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_plane	*init_plane(t_texture *texture, int a, int b, int d)
{
	t_plane	*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return (NULL);
	plane->a = a;
	plane->b = b;
	plane->d = d;
	plane->add = texture;
	return (plane);
}

static t_plane	*ft_init_plane(t_game *game, int x, int y, char dir)
{
	t_plane	*plane;

	plane = NULL;
	if (dir == 'L')
		plane = init_plane(game->file.texture_we, 1, 0, -x);
	else if (dir == 'R')
		plane = init_plane(game->file.texture_ea, -1, 0, x);
	else if (dir == 'T')
		plane = init_plane(game->file.texture_no, 0, 1, -y);
	else if (dir == 'B')
		plane = init_plane(game->file.texture_so, 0, -1, y);
	return (plane);
}

static int	ft_plane_to_list(t_game *game, t_list **lst, t_plane *plane)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(plane);
	if (!new_lst)
	{
		free(plane);
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	}
	ft_lstadd_back(lst, new_lst);
	return (0);
}

int	ft_create_plane(t_game *game, t_list **lst, int *pos, char dir)
{
	t_plane	*plane;

	plane = ft_search_plane(*lst, pos[0], pos[1], dir);
	if (!plane)
	{
		plane = ft_init_plane(game, pos[0], pos[1], dir);
		if (!plane)
			return (ft_trash_game(game, allocation_fail, -1, "\n"));
		ft_plane_to_list(game, lst, plane);
		ft_sort_planes(*lst);
	}
	return (0);
}

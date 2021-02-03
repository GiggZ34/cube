/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:45:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/01 13:20:13 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall		*ft_init_plane(t_game *game, int x, int y, char dir)
{
	t_wall	*wall;

	if (!(wall = ft_calloc(sizeof(t_wall), 1)))
		return (0);
	wall->plane.a = 0;
	wall->plane.b = 0;
	wall->plane.c = 0;
	wall->width = 0;
	wall->pos.x = x;
	wall->pos.y = y;
	wall->n_tab_size = 1;
	if (!(wall->tab_size = ft_calloc(sizeof(int), ft_max(game->file->height_map, game->file->width_map))))
	{
		free(wall);
		return (NULL);
	}
	if (dir == 'R' || dir == 'L')
	{
		wall->tab_size[wall->n_tab_size - 1] = y;
		wall->plane.a = 1;
		wall->plane.d = -x;
		if (dir == 'R')
			wall->texture =	game->file->texture_we;
		else
			wall->texture = game->file->texture_ea;
	}
	else if (dir == 'T' || dir == 'B')
	{
		wall->tab_size[wall->n_tab_size - 1] = x;
		wall->plane.b = 1;
		wall->plane.d = -y;
		if (dir == 'T')
			wall->texture =	game->file->texture_no;
		else
			wall->texture = game->file->texture_so;
	}
	return (wall);
}

static int			ft_plane_to_list(t_list **plane, t_wall *wall)
{
	t_list	*lst;

	if (!(lst = ft_lstnew(wall)))
		return (3);
	ft_lstadd_back(plane, lst);
	return (0);
}

static t_wall		*ft_search_plane(t_list *lst, int x, int y, char dir)
{
	t_wall	*wall;

	while (lst)
	{
		wall = lst->content;
		if (dir == 'R' || dir == 'L')
		{
			if (wall->plane.a == 1 && wall->plane.d == -x)
			{
				wall->n_tab_size++;
				wall->tab_size[wall->n_tab_size - 1] = y;
				wall->pos.y = ft_min(wall->pos.y, y);
				return (wall);
			}
		}
		else if (dir == 'T' || dir == 'B')
		{
			if (wall->plane.b == 1 && wall->plane.d == -y)
			{
				wall->n_tab_size++;
				wall->tab_size[wall->n_tab_size - 1] = x;
				wall->pos.x = ft_min(wall->pos.x, x);
				return (wall);
			}
		}
		lst = lst->next;
	}
	return (NULL);
}

int					ft_create_plane(t_game *game, t_list **lst, int *pos, char dir)
{
	t_wall	*wall;

	if (!(wall = ft_search_plane(*lst, pos[0], pos[1], dir)))
	{
		if (!(wall = ft_init_plane(game, pos[0], pos[1], dir)))
			return (3);
		if (ft_plane_to_list(lst, wall))
			return (3);
	}
	return (0);
}

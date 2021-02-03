/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_to_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:04:40 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 12:51:40 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall	*ft_search_to_list(t_list *lst, int *pos, char dir)
{
	t_wall	*wall;

	while (lst)
	{
		wall = lst->content;
		if (dir == 'R' || dir == 'L')
		{
			if (wall->plane.d == -(pos[0]) && (pos[1] >= wall->pos.y
									&& pos[1] <= wall->pos.y + wall->width))
				return (wall);
		}
		else if (dir == 'T' || dir == 'B')
		{
			if (wall->plane.d == -(pos[1]) && (pos[0] >= wall->pos.x
									&& pos[0] <= wall->pos.x + wall->width))
				return (wall);
		}
		lst = lst->next;
	}
	return (NULL);
}

int				ft_wall_to_view(t_game *game, t_list **lst, int *pos, char dir)
{
	t_list	*lst_view;
	t_wall	*wall;

	if ((wall = ft_search_to_list(game->player->view.lst_walls, pos, dir)))
		return (0);
	if (!(wall = ft_search_to_list(*lst, pos, dir)))
		return (15);
	if (!(lst_view = ft_lstnew(wall)))
		return (3);
	ft_lstadd_back(&game->player->view.lst_walls, lst_view);
	return (0);
}

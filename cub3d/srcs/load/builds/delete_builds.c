/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:39:31 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 13:03:46 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_wall(t_wall *b1, t_wall *b2)
{
	return (b1->id != b2->id
			&& b1->pos.x >= b2->pos.x
			&& b1->pos.x + b1->width <= b2->pos.x + b2->width
			&& b1->pos.y >= b2->pos.y
			&& b1->pos.y + b1->height <= b2->pos.y + b2->height);
}

void	ft_del_wall(void *content)
{
	free(content);
}

int		ft_delete_walls(t_list **lst_walls)
{
	t_list	*lst;
	t_wall	*wall;
	t_list	*current;
	t_list	*next;
	t_wall	*content;

	lst = *lst_walls;
	while (lst)
	{
		wall = lst->content;
		current = *lst_walls;
		while (current)
		{
			content = current->content;
			next = current->next;
			if (ft_check_wall(content, wall))
				ft_lstclearone(lst_walls, current, &ft_del_wall);
			current = next;
		}
		lst = lst->next;
	}
	return (0);
}

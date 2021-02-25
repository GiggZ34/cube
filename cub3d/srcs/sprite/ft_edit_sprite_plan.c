/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_sprite_plan.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:16:53 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/15 11:17:14 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_edit_sprite_plane(t_list *lst, t_vector normal)
{
	t_sprite	*sprite;

	while (lst)
	{
		sprite = lst->content;
		sprite->plane.a = -normal.x;
		sprite->plane.b = -normal.y;
		sprite->plane.c = normal.z;
		sprite->plane.d = -(sprite->plane.a * sprite->position.x
							+ sprite->plane.b * sprite->position.y
							+ sprite->plane.c * sprite->position.z);
		lst = lst->next;
	}
	return (0);
}

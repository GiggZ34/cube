/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_sprite_plan.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:16:53 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/09 13:14:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_edit_sprite_plane(t_list *lst, t_vector normal)
{
	t_sprite	*sprite;

	while (lst)
	{
		sprite = lst->content;
		sprite->plane.a = normal.x;
		sprite->plane.b = normal.y;
		sprite->plane.d = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
		lst = lst->next;
	}
	return (0);
}

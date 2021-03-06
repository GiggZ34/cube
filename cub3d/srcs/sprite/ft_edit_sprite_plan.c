/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_sprite_plan.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:16:53 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/04 15:29:41 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_edit_sprite_plane(t_sprite *sprite, t_dot pos_player)
{
	sprite->normal = ft_create_vector(sprite->position, pos_player);
	sprite->plane.a = sprite->normal.x;
	sprite->plane.b = sprite->normal.y;
	sprite->plane.c = 0;
	sprite->plane.d = -(sprite->plane.a * sprite->position.x
										+ sprite->plane.b * sprite->position.y);
	return (0);
}

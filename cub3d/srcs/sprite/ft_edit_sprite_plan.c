/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_sprite_plan.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:16:53 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/07 16:41:37 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_edit_sprite_plane(t_sprite *sprite, t_dot pos_player)
{
	sprite->normal = ft_create_vector(sprite->position, pos_player);
	sprite->vec_write = ft_rotate_vector(sprite->normal, M_PI / 2, 'z');
	sprite->vec_write = ft_vec_norm_define(sprite->vec_write, sprite->width / 2);
	sprite->frist_px.x = sprite->position.x + sprite->vec_write.x;
	sprite->frist_px.y = sprite->position.y + sprite->vec_write.y;
	sprite->frist_px.z = 0;
	sprite->plane.a = sprite->normal.x;
	sprite->plane.b = sprite->normal.y;
	sprite->plane.c = 0;
	sprite->plane.d = -(sprite->plane.a * sprite->position.x
										+ sprite->plane.b * sprite->position.y);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vectors_collides.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:19:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/07 22:25:10 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_rotate_vectors_collides(t_player *player, double angle)
{
	player->view.view = ft_rotate_vector(player->view.view, angle, 'z');
	player->collide.top = ft_rotate_vector(player->collide.top, angle, 'z');
	player->collide.bottom = ft_rotate_vector(player->collide.bottom, angle, 'z');
	player->collide.left = ft_rotate_vector(player->collide.left, angle, 'z');
	player->collide.right = ft_rotate_vector(player->collide.right, angle, 'z');
	return (0);
}

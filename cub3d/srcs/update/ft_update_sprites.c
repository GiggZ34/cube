/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:42:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/10 22:44:15 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_search_sprites(t_sprite *sprite, t_list **begin, t_player *player)
{
	t_vector	vec;
	t_list		*lst;
	int			dist;

	vec = ft_create_vector(sprite->position, player->position);
	dist = pow(player->position.x - sprite->position.x, 2) +
								pow(player->position.y - sprite->position.y, 2);
	if (ft_dot_product(player->collide.top, vec) < FOV_COS && dist <= FOV_DIST)
	{
		lst = ft_lstnew(sprite);
		ft_lstadd_back(begin, lst);
	}
}

static void ft_play(void *s)
{
	if (s)
		return ;
	return ;
}

int		    ft_update_sprites(t_list *lst_sprites, t_player *player)
{
	t_sprite	*sprite;

	ft_lstclear(&(player->view.sprites_in_fov), &ft_play, 0);
	while (lst_sprites)
	{
		sprite = lst_sprites->content;
		ft_edit_sprite_plane(sprite, player->view.view);
		sprite->position.y -= 0.0;
		ft_search_sprites(sprite, &(player->view.sprites_in_fov), player);
		lst_sprites = lst_sprites->next;
	}
	return (0);
}

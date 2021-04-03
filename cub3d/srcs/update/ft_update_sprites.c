/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:42:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/02 19:23:31 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sort_lst_sprite(t_list **begin)
{
	t_list		*lst;
	t_list		*lst_comp;
	t_sprite	*s;
	t_sprite	*s_comp;

	lst = *begin;
	while (lst)
	{
		s = lst->content;
		lst_comp = lst->next;
		while (lst_comp)
		{
			s_comp = lst_comp->content;
			if (s_comp->dist_to_player < s->dist_to_player)
				ft_lst_swap(lst, lst_comp);
			lst_comp = lst_comp->next;
		}
		lst = lst->next;
	}
}

static int	ft_search_sprites(t_sprite *s, t_list **begin, t_player *player)
{
	t_list		*lst;

	s->sprite_to_player = ft_create_vector(s->position, player->position);
	s->dist_to_player = pow(player->position.x - s->position.x, 2)
		+ pow(player->position.y - s->position.y, 2);
	if (ft_dot_product(player->collide.top, s->sprite_to_player) < FOV_COS)
	{
		lst = ft_lstnew(s);
		ft_plane_inter_nom(&s->plane, player->position);
		ft_lstadd_back(begin, lst);
		return (1);
	}
	return (0);
}

static void	ft_play(void *s)
{
	if (s)
		return ;
	return ;
}

int	ft_update_sprites(t_list *lst_sprites, t_player *player)
{
	t_sprite	*sprite;

	ft_lstclear(&(player->view.sprites_in_fov), &ft_play, 0);
	while (lst_sprites)
	{
		sprite = lst_sprites->content;
		ft_edit_sprite_plane(sprite, player->view.view);
		ft_search_sprites(sprite, &(player->view.sprites_in_fov), player);
		ft_sort_lst_sprite(&(player->view.sprites_in_fov));
		lst_sprites = lst_sprites->next;
	}
	return (0);
}

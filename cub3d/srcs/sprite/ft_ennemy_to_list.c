/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ennemy_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:00:39 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 13:11:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_ennemy_to_view_list(t_game *game, t_sprite *sprite)
{
	t_list	*new_lst;

	if (!(new_lst = ft_lstnew(sprite)))
		return (3);
	ft_lstadd_back(&(game->player->view.lst_sprites), new_lst);
	return (0);
}

int				ft_ennemy_to_list(t_game *game, int x, int y)
{
	t_list		*lst;
	t_sprite	*sprite;

	lst = game->lst_sprites;
	while (lst)
	{
		sprite = lst->content;
		if(x == (int)sprite->position.x && y == (int)sprite->position.y)
			if (ft_ennemy_to_view_list(game, sprite))
				return (game->file->error_code);
		lst = lst->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:26:07 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 15:29:36 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_init_ennemy(t_game *game, int x, int y)
{
	t_list		*new_lst;
	t_sprite	*ennemy;

	if (!(ennemy = ft_calloc(sizeof(*ennemy), 1)))
		return (3);
	ennemy->tile_sheet = game->file->texture_s;
	ennemy->type = "ennemy";
	ennemy->position.x = x;
	ennemy->position.y = y;
	ennemy->position.z = ennemy->tile_sheet->height;
	ennemy->vx = 0;
	ennemy->vy = 0;
	ennemy->state = 0;
	ennemy->angle = 0;
	if (!(new_lst = ft_lstnew(ennemy)))
		return (3);
	ft_lstadd_back(&(game->lst_sprites), new_lst);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:26:07 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/08 01:37:46 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_init_ennemy(t_game *game, int x, int y)
{
	t_list		*new_lst;
	t_sprite	*ennemy;

	if (!(ennemy = ft_calloc(sizeof(t_sprite), 1)))
		return (3);
	ennemy->tile_sheet = game->file->texture_s;
	ennemy->position.x = x + 0.5;
	ennemy->position.y = y + 0.5;
	ennemy->position.z = 0;
	ennemy->ratio = 0.7;
	ennemy->height = ennemy->tile_sheet->height;
	ennemy->width = ennemy->tile_sheet->size_line / ennemy->height * ennemy->ratio;
	ennemy->height = ennemy->ratio;
	if (!(new_lst = ft_lstnew(ennemy)))
	{
		free(ennemy);
		return (3);
	}
	ft_lstadd_back(&game->lst_sprites, new_lst);
	return (0);
}

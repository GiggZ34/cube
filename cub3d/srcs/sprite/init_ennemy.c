/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:26:07 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/09 13:09:00 by grivalan         ###   ########lyon.fr   */
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
	ennemy->position.x = x;
	ennemy->position.y = y;
	ennemy->plane.a = -0.01;
	ennemy->plane.d = sqrt(pow(x, 2) + pow(y, 2));
	ennemy->plane.add = ennemy;
	ennemy->position.z = ennemy->tile_sheet->height;
	if (!(new_lst = ft_lstnew(ennemy)))
	{
		free(ennemy);
		return (3);
	}
	ft_lstadd_back(&game->lst_sprites, new_lst);
	if (!(new_lst = ft_lstnew(&ennemy->plane)))
		return (3);
	ft_lstadd_back(&(game->lst_planes_sprites), new_lst);
	return (0);
}

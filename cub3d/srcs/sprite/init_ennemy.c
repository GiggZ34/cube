/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:26:07 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:16:38 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_ennemy(t_game *game, int x, int y)
{
	t_list		*new_lst;
	t_sprite	*ennemy;

	ennemy = ft_calloc(sizeof(t_sprite), 1);
	if (!ennemy)
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	ennemy->tile_sheet = game->file.texture_s;
	ennemy->position.x = x + 0.5;
	ennemy->position.y = y + 0.5;
	ennemy->position.z = 0;
	ennemy->ratio = 0.7;
	ennemy->height = ennemy->tile_sheet->height;
	ennemy->width = ennemy->tile_sheet->size_line
		/ ennemy->height * ennemy->ratio;
	ennemy->height = ennemy->ratio;
	new_lst = ft_lstnew(ennemy);
	if (!new_lst)
	{
		free(ennemy);
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	}
	ft_lstadd_back(&game->lst_sprites, new_lst);
	return (0);
}

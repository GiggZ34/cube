/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 11:32:57 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*ft_init_player(t_game *game, int x, int y, char dir)
{
	t_dot	tmp;

	if (!(game->player = ft_calloc(sizeof(t_player), 1)))
		return (0);
	game->player->position.x = x;
	game->player->position.y = y;
	game->player->position.z = 0.5;
	tmp = game->player->position;
	if (dir == 'N')
	{
		game->player->dir = 0;
		tmp.y -= 0.1;
	}
	else if (dir == 'S')
	{
		game->player->dir = 180;
		tmp.y += 0.1;
	}
	else if (dir == 'E')
	{
		game->player->dir = 90;
		tmp.x -= 0.1;
	}
	else if (dir == 'W')
	{
		game->player->dir = 270;
		tmp.x += 0.1;
	}
	game->player->vx = 0;
	game->player->vy = 0;
	game->player->live = 100;
	game->player->tile_sheet = NULL;
	game->player->view.lst_walls = NULL;
	game->player->view.view = ft_normal_vector_calculator(game->player->position, tmp);
	return (game->player);
}

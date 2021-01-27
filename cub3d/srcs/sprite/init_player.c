/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/22 09:17:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*ft_init_player(t_game *game, int x, int y, char dir)
{
	t_dot	tmp;

	if (!(game->player = ft_calloc(sizeof(t_player), 1)))
		return (0);
	game->player->dir = dir;
	game->player->position.x = x;
	game->player->position.y = y;
	game->player->position.z = 0.5;
	tmp = game->player->position;
	if (dir == 'N')
		tmp.y--;
	else if (dir == 'S')
		tmp.y++;
	else if (dir == 'E')
		tmp.x--;
	else if (dir == 'W')
		tmp.x++;
	game->player->view = ft_normal_vector_calculator(game->player->position, tmp);
			printf("norm | %f\n",ft_norm_vector_calculate(game->player->view));
	game->player->view = ft_rotate_vector(game->player->view, ft_deg_to_rad(-30), 'x');
			printf("norm | %f\n",ft_norm_vector_calculate(game->player->view));
	game->player->view = ft_rotate_vector(game->player->view, ft_deg_to_rad(30), 'z');
			printf("norm | %f\n",ft_norm_vector_calculate(game->player->view));
	game->player->vx = 0;
	game->player->vy = 0;
	game->player->live = 100;
	game->player->tile_sheet = NULL;
	return (game->player);
}

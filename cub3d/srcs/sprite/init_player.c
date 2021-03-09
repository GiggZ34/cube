/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 14:57:18 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*ft_init_player(t_game *game, int x, int y, char dir)
{
	double	angle;

	if (!(game->player = ft_calloc(sizeof(t_player), 1)))
		return (0);
	game->player->position.x = x + 0.5;
	game->player->position.y = y + 0.5;
	game->player->position.z = 1 - 0.5;
	if (ft_init_tab_vector(game, game->player->position))
		return (NULL);
	if (dir == 'E')
		angle = M_PI / 2;
	else if (dir == 'S')
		angle = M_PI;
	else if (dir == 'W')
		angle = 3 / 2 * M_PI;
	else
		angle = 0;
	game->player->angle_z = angle;
	game->player->angle_x = 0;
	game->player->live = 100;
	game->player->walk_speed_max = 1.2;
	game->player->run_speed_max = 2.5;
	return (game->player);
}

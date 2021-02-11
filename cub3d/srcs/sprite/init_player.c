/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:33:59 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/11 14:12:05 by grivalan         ###   ########lyon.fr   */
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
	game->player->position.z = 0.5;
	if (ft_init_tab_vector(game, game->player->position))
		return (NULL);
	if (dir == 'S')
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, (angle = M_PI / 2), 'z');
	else if (dir == 'W')
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, (angle = M_PI), 'z');
	else if (dir == 'N')
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, (angle = 3 / 2 * M_PI), 'z');
	else
		angle = 0;
	game->player->angle = angle;
	game->player->live = 100;
	game->player->walk_speed_max = 10;
	return (game->player);
}

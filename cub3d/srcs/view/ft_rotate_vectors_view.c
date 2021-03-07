/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vectors_view.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:19:27 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/07 03:33:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_rotate_vectors_view(t_game *game, t_vector *tab, double angle, char dir)
{
	int	i;
	int	end;

	i = -1;
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	game->player->angle += angle;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	else if (game->player->angle >= 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	end = game->screen.height * game->screen.size;
	while (++i < end)
		tab[i] = ft_rotate_vector(tab[i], angle, dir);
	game->player->view.view = ft_rotate_vector(game->player->view.view, angle, dir);
	return (0);
}

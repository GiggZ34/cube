/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 14:50:40 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 18:22:17 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_change_resolution(t_game *game, int fd)
{
	if (mlx_get_screen_size(game->mlx, &game->screen.max_x,
			&game->screen.max_y) == -1)
		ft_trash_game(game, crash_mlx_ft, fd, "In ft_change_resolution");
	if (game->screen.width > game->screen.max_x)
		game->screen.width = game->screen.max_x;
	if (game->screen.height > game->screen.max_y)
		game->screen.height = game->screen.max_y;
	return (0);
}

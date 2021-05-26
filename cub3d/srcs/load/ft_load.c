/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:19:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 16:49:46 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_load_textures(t_game *game)
{
	game->sky_ground.ground_plane.c = 1;
	game->sky_ground.sky_plane.c = 1;
	game->sky_ground.sky_plane.d = -1;
	ft_load_tilesheet_obj(game, "./textures/gun_animation.xpm");
	return (0);
}

int	ft_load(char *dir_file, t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_trash_game(game, mlx_creation_fail, 1, ""));
	ft_init_file(&game->file, game, dir_file);
	ft_load_textures(game);
	return (0);
}

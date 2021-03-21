/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:19:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 02:25:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_load_textures_ground(t_game *game)
{
	if (!(game->sky_ground.ground_texture.ptr = mlx_xpm_file_to_image(
									game->mlx,
									"./textures/ground-6.xpm",
									&(game->sky_ground.ground_texture.width),
									&(game->sky_ground.ground_texture.height))))
		return (ft_trash_game(game, allocation_fail, 1));
	if (!(game->sky_ground.ground_texture.color = (int*)mlx_get_data_addr(
								game->sky_ground.ground_texture.ptr,
								&game->sky_ground.ground_texture.bits_per_pixel,
								&game->sky_ground.ground_texture.size_line,
								&game->sky_ground.ground_texture.endian)))
		return (ft_trash_game(game, allocation_fail, 1));
	game->sky_ground.ground_texture.size_line /= 4;
	game->sky_ground.ground_plane.a = 0;
	game->sky_ground.ground_plane.b = 0;
	game->sky_ground.ground_plane.c = 1;
	game->sky_ground.ground_plane.d = 0;
	return (0);
}

static int	ft_load_textures_sky(t_game *game)
{
	if (!(game->sky_ground.sky_texture.ptr = mlx_xpm_file_to_image(
								game->mlx,
								"./textures/ceil-3.xpm",
								&(game->sky_ground.sky_texture.width),
								&(game->sky_ground.sky_texture.height))))
		return (ft_trash_game(game, allocation_fail, 1));
	if (!(game->sky_ground.sky_texture.color = (int*)mlx_get_data_addr(
								game->sky_ground.sky_texture.ptr,
								&game->sky_ground.sky_texture.bits_per_pixel,
								&game->sky_ground.sky_texture.size_line,
								&game->sky_ground.sky_texture.endian)))
		return (ft_trash_game(game, allocation_fail, 1));
	game->sky_ground.sky_texture.size_line /= 4;
	game->sky_ground.sky_plane.a = 0;
	game->sky_ground.sky_plane.b = 0;
	game->sky_ground.sky_plane.c = 1;
	game->sky_ground.sky_plane.d = -1;
	return (0);
}

static int	ft_load_textures(t_game *game)
{
	ft_load_textures_ground(game);
	ft_load_textures_sky(game);
	ft_load_tilesheet_obj(game, "./textures/gun_animation.xpm");
	return (0);
}

int			ft_load(char *dir_file, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (!(game->mlx = mlx_init()))
		return (ft_trash_game(game, allocation_fail, 1));
	ft_init_file(&game->file, game, dir_file);
	ft_load_textures(game);
	if (game->file.error_code != 0)
		return (game->file.error_code);
	return (game->file.error_code);
}

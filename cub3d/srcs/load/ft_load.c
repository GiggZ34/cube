/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:19:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/13 21:16:25 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_ratio_dim_obj(t_game *game, t_player *player)
{
	double	ratio_height;
	double	ratio_width;

	player->guns.height = game->screen.height / 3;
	player->guns.width = game->screen.size / 3;
	ratio_height = player->guns.obj_texture.height / player->guns.height;
	ratio_width = player->guns.obj_texture.size_line / player->guns.width;
	return (ft_max(ratio_height, ratio_width));
}

static int	ft_load_texture_obj(t_game *game, char *path)
{
	if (!(game->player->guns.obj_texture.ptr = mlx_xpm_file_to_image(game->mlx,
									path,
									&(game->player->guns.obj_texture.width),
									&(game->player->guns.obj_texture.height))))
		return (3);
	if (!(game->player->guns.obj_texture.color = (int*)mlx_get_data_addr(
								game->player->guns.obj_texture.ptr,
								&game->player->guns.obj_texture.bits_per_pixel,
								&game->player->guns.obj_texture.size_line,
								&game->player->guns.obj_texture.endian)))
		return (3);
	game->player->guns.obj_texture.size_line /= 4;
	game->player->guns.ratio = ft_ratio_dim_obj(game, game->player);
	game->player->guns.width /= game->player->guns.ratio;
	game->player->guns.height /= game->player->guns.ratio;
	game->player->guns.position.x = game->screen.width / 2;
	game->player->guns.position.y = game->screen.height
						- game->player->guns.height / game->player->guns.ratio;
	return (0);
}

static int	ft_load_textures_ground(t_game *game)
{
	if (!(game->sky_ground.ground_texture.ptr = mlx_xpm_file_to_image(
									game->mlx,
									"./textures/ceil-3.xpm",
									&(game->sky_ground.ground_texture.width),
									&(game->sky_ground.ground_texture.height))))
		return (3);
	if (!(game->sky_ground.ground_texture.color = (int*)mlx_get_data_addr(
								game->sky_ground.ground_texture.ptr,
								&game->sky_ground.ground_texture.bits_per_pixel,
								&game->sky_ground.ground_texture.size_line,
								&game->sky_ground.ground_texture.endian)))
		return (3);
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
								"./textures/ground-3.xpm",
								&(game->sky_ground.sky_texture.width),
								&(game->sky_ground.sky_texture.height))))
		return (3);
	if (!(game->sky_ground.sky_texture.color = (int*)mlx_get_data_addr(
								game->sky_ground.sky_texture.ptr,
								&game->sky_ground.sky_texture.bits_per_pixel,
								&game->sky_ground.sky_texture.size_line,
								&game->sky_ground.sky_texture.endian)))
		return (3);
	game->sky_ground.sky_texture.size_line /= 4;
	game->sky_ground.sky_plane.a = 0;
	game->sky_ground.sky_plane.b = 0;
	game->sky_ground.sky_plane.c = 1;
	game->sky_ground.sky_plane.d = 1;
	return (0);
}

static int	ft_load_textures(t_game *game)
{
	if (ft_load_textures_ground(game))
		return (3);
	if (ft_load_textures_sky(game))
		return (3);
	if (ft_load_texture_obj(game, "./textures/gun-1.xpm"))
		return (3);
	return (0);
}

int			ft_load(char *dir_file, t_game *game)
{
	t_file	*file;

	ft_bzero(game, sizeof(t_game));
	if (!(game->file = ft_calloc(sizeof(t_file), 1)))
		return (3);
	file = game->file;
	if (!(game->mlx = mlx_init()))
		return (FAIL_EXIT);
	ft_init_file(file, game, dir_file);
	ft_load_textures(game);
	if (file->error_code != 0)
		return (file->error_code);
	return (file->error_code);
}

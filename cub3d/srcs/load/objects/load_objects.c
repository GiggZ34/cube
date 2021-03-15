/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:02:45 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/15 14:12:54 by grivalan         ###   ########lyon.fr   */
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

static void	ft_define_data_tilesheet(t_game *game, t_player *player)
{
	player->guns.obj_texture.size_line /= 4;
	player->guns.width = player->guns.obj_texture.size_line / NB_IMG_ANIM_GUNS;
	player->guns.height = player->guns.obj_texture.height / NB_ANIM_GUNS;
	player->guns.ratio = ft_ratio_dim_obj(game, player);
	player->guns.position.x = game->screen.size - game->screen.size / 3;
	player->guns.position.y = game->screen.height - game->screen.height / 3;
}

static t_player_anim	ft_define_nb_img(int id)
{
	if (id = 0)
		return (anim_rest);
	else if (id = 1)
		return (anim_reload);
	else
		return (anim_shoot);
}

static void	ft_create_screen(t_game *game, t_player *player, int id)
{
	int nb_img;

	nb_img = ft_define_nb_img(id);
	player->gun[id] = ft_calloc(sizeof(t_screen), nb_img + 1);
	if (player->gun[id] == NULL)
		exit(1);
	ft_init_screen(game, player->gun[id], nb_img, id);
}

int			ft_load_tilesheet_obj(t_game *game, char *path)
{
	int	i;

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
	ft_define_data_tilesheet(game, game->player);
	i = -1;
	while (++i < NB_IMG_ANIM_GUNS)
		ft_create_screen(game, game->player, i);
	return (0);
}

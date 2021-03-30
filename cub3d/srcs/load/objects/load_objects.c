/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:02:45 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/30 16:01:04 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_ratio_dim_obj(t_game *game, t_player *player)
{
	double	ratio_height;
	double	ratio_width;
	int		width;
	int		height;

	height = game->screen.height / 2;
	width = game->screen.width;
	ratio_height = (double)height / (double)player->guns.height;
	ratio_width = (double)width / (double)player->guns.width;
	game->player.guns.ratio_pos = ft_min(ratio_height, ratio_width);
	ratio_height = (double)player->guns.height / (double)height;
	ratio_width = (double)player->guns.width / (double)width;
	game->player.guns.ratio_size = ft_max(ratio_height, ratio_width);
}

static void	ft_define_data_tilesheet(t_game *game, t_player *player)
{
	player->guns.obj_texture.size_line /= 4;
	player->guns.width = player->guns.obj_texture.width / nb_img_anim;
	player->guns.height = player->guns.obj_texture.height / nb_anim;
	ft_ratio_dim_obj(game, player);
	player->guns.position.x = game->screen.width / 2 - (player->guns.width * player->guns.ratio_pos) / 2;
	player->guns.position.y = game->screen.height - (player->guns.height * player->guns.ratio_pos);
}

static int	ft_create_screen(t_game *game, t_player *player, int state)
{
	int nb_img;

	nb_img = ft_define_nb_anim(state);
	player->gun[state] = ft_calloc(sizeof(t_screen), nb_img);
	if (player->gun[state] == NULL)
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	ft_init_screen(game, player->gun[state], nb_img, state);
	return (0);
}

int			ft_load_tilesheet_obj(t_game *game, char *path)
{
	int	state;

	if (!(game->player.guns.obj_texture.ptr = mlx_xpm_file_to_image(game->mlx,
									path,
									&(game->player.guns.obj_texture.width),
									&(game->player.guns.obj_texture.height))))
		return (ft_trash_game(game, load_texture_fail, -1, "\n"));
	if (!(game->player.guns.obj_texture.color = (int*)mlx_get_data_addr(
								game->player.guns.obj_texture.ptr,
								&game->player.guns.obj_texture.bits_per_pixel,
								&game->player.guns.obj_texture.size_line,
								&game->player.guns.obj_texture.endian)))
		return (ft_trash_game(game, color_generation_fail, -1, "\n"));
	ft_define_data_tilesheet(game, &game->player);
	game->player.gun = ft_calloc(sizeof(t_screen*), nb_anim);
	if (!game->player.gun)
		ft_trash_game(game, allocation_fail, game->file.fd, "\n");
	state = -1;
	while (++state < nb_anim)
		ft_create_screen(game, &game->player, state);
	mlx_destroy_image(game->mlx, game->player.guns.obj_texture.ptr);
	ft_bzero(&game->player.guns, sizeof(t_obj));
	return (0);
}

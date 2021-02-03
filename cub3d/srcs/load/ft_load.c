/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:19:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 09:39:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_game(t_game *game)
{
	game->lst_planes = NULL;
	game->lst_sprites = NULL;
	game->lst_walls_bottom = NULL;
	game->lst_walls_left = NULL;
	game->lst_walls_right = NULL;
	game->lst_walls_top = NULL;
	game->player = NULL;
}

int		ft_load(char *dir_file, t_game *game)
{
	t_file	*file;

	if (!(game->file = ft_calloc(sizeof(t_file), 1)))
		return (3);
	file = game->file;
	if (!(game->mlx = mlx_init()))
		return (FAIL_EXIT);
	ft_init_game(game);
	ft_init_file(file, game, dir_file);
	if (file->error_code != 0)
		return (file->error_code);
	game->window = mlx_new_window(game->mlx,
						game->screen.width, game->screen.height, "Cub3D");
	return (file->error_code);
}

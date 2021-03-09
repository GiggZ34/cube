/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:19:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 13:45:33 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_load(char *dir_file, t_game *game)
{
	t_file	*file;

	ft_bzero(game, sizeof(t_game));
	if (!(game->file = ft_calloc(sizeof(t_file), 1)))
		return (3);
	file = game->file;
	if (!(game->mlx = mlx_init()))
		return (FAIL_EXIT);
	ft_init_file(file, game, dir_file);
	mlx_mouse_hide();
	if (file->error_code != 0)
		return (file->error_code);
	return (file->error_code);
}

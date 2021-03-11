/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:21:03 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 12:39:14 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_screen(t_game *game)
{
	if (!(game->screen.ptr = mlx_new_image(game->mlx,
									game->screen.width, game->screen.height)))
		return (game->file->error_code = 3);
	if (!(game->screen.color = (int*)mlx_get_data_addr(game->screen.ptr,
				&game->screen.bit, &game->screen.size, &game->screen.endian)))
		return (game->file->error_code = 3);
	game->screen.w_vec = (1 / FOV) / game->screen.size;
	game->screen.size /= 4;
	return (game->file->error_code);
}

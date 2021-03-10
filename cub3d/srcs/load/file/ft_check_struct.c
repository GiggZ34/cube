/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:57:26 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/10 17:12:57 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_change_resolution(t_game *game)
{
	int	width_screen;
	int	height_screen;

	if (mlx_get_screen_size(game->mlx, &width_screen, &height_screen) == -1)
		return (3);
	if (game->screen.width <= 0)
		return (11);
	else if (game->screen.width > width_screen)
		game->screen.width = width_screen;
	if (game->screen.height <= 0)
		return (11);
	else if (game->screen.height > height_screen)
		game->screen.height = height_screen;
	return (0);
}

int			ft_check_struct(t_game *game)
{
	if (game->screen.width < 640 || game->screen.width > 2560
			|| game->screen.height < 480 || game->screen.height > 1400)
		if ((game->file->error_code = ft_change_resolution(game)) != 0)
			return (ft_error_file(game->file, game->file->error_code, ""));
	return (0);
}

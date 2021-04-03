/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:26:33 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/02 11:45:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mini_map(t_game *game)
{
	t_file *file;
	int	i;
	int	j;
	int	k;
	int	l;
	int	color;
	int	px_w;
	int	px_h;

	px_w = 10;
	px_h = 10;
	i = -1;
	file = game->file;
	while (file->map[++i])
	{
		k = -1;
		while (++k < 5)
		{
			j = -1;
			while (file->map[i][++j])
			{
				l = -1;
				if (file->map[i][j] == ' ')
					l = 5 - 1;
				while (++l < 5)
				{
					if (ft_in_array(file->map[i][j], "02") != -1)
						color = ft_color_generate(20, 133, 160, 0);
					else if (file->map[i][j] == '1')
						color = ft_color_generate(208, 190, 250, 0);
					else if (ft_in_array(file->map[i][j], "NSEW") != -1)
						color = ft_color_generate(255, 0, 0, 0);
					mlx_pixel_put(game->mlx, game->window, px_w + l, px_h + k, color);
				}
				px_w += l;
			}
			px_w = 10;
		}
		px_h += k;
	}
	mlx_pixel_put(game->mlx, game->window, 10 + (game->player->position.x / 64) * 5, 10 + (game->player->position.y / 64) * 5, ft_color_generate(255, 0, 0, 0));
	return (0);
}

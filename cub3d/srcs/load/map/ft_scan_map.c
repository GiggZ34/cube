/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:30:41 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/26 15:36:56 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_scan_horizontal(t_game *game, char **map, int i, int j)
{
	t_file		*file;

	file = game->file;
	if (map[i][j] == '1')
	{
		map[i][j] = 'w';
		if ((file->error_code = ft_create_plane(game, i, j, 'H')) != 0)
			file->error_code = 3;
	}
	if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
		file->error_code = 3;
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_vertical(t_game *game, char **map, int i, int j)
{
	t_file		*file;

	file = game->file;
	if (map[i][j] == '1')
	{
		map[i][j] = 'w';
		if ((file->error_code = ft_create_plane(game, i, j, 'V')) != 0)
			file->error_code = 3;
	}
	if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
		file->error_code = 3;
	ft_scan_map(game, map, i, j);
}

void		ft_scan_map(t_game *game, char **map, int i, int j)
{
	t_file	*file;

	file = game->file;
	if (!file->error_code)
	{
		if (((i == ft_count_array(map) || j == (int)ft_strlen(map[i])
				|| i == 0 || j == 0) && map[i][j] != 'w')
				|| ft_in_array(map[i][j], "02cwNSEW") == -1)
			ft_error_file(file, 2, ft_search_error(&file->map[i], j, i));
		else if (map[i][j] != 'w' && map[i][j] != 'c')
		{
			map[i][j] = 'c';
			ft_scan_horizontal(game, map, i, j - 1);
			ft_scan_horizontal(game, map, i, j + 1);
			ft_scan_vertical(game, map, i - 1, j);
			ft_scan_vertical(game, map, i + 1, j);
		}
	}
}

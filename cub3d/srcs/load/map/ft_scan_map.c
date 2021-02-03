/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:30:41 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 12:02:45 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_scan_horizontal_left(t_game *game, char **map, int i, int j)
{
	t_file		*file;
	int			pos[2];

	file = game->file;
	if (map[i][j] == '1')
	{
		pos[0] = j + 1;
		pos[1] = i;
		file->error_code = ft_create_plane(game, &game->lst_walls_left, pos, 'L');
	}
	else if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
		file->error_code = 3;
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_vertical_top(t_game *game, char **map, int i, int j)
{
	t_file		*file;
	int			pos[2];

	file = game->file;
	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i + 1;
		file->error_code = ft_create_plane(game, &game->lst_walls_top, pos, 'T');
	}
	else if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
		file->error_code = 3;
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_horizontal_right(t_game *game, char **map, int i, int j)
{
	t_file		*file;
	int			pos[2];

	file = game->file;
	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i;
		file->error_code = ft_create_plane(game, &game->lst_walls_right, pos, 'R');
	}
	if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
		file->error_code = 3;
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_vertical_bottom(t_game *game, char **map, int i, int j)
{
	t_file		*file;
	int			pos[2];

	file = game->file;
	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i;
		file->error_code = ft_create_plane(game, &game->lst_walls_bottom, pos, 'B');
	}
	else if (map[i][j] == '2' && ft_init_ennemy(game, j, i))
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
				|| i == 0 || j == 0) && map[i][j] != '1')
				|| ft_in_array(map[i][j], "012cNSEW") == -1)
			ft_error_file(file, 2, ft_search_error(&file->map[i], j, i));
		else if (map[i][j] == '0' || map[i][j] == '2'
								|| ft_in_array(map[i][j], "NSEW") != -1)
		{
			map[i][j] = 'c';
			ft_scan_horizontal_left(game, map, i, j - 1);
			ft_scan_horizontal_right(game, map, i, j + 1);
			ft_scan_vertical_top(game, map, i - 1, j);
			ft_scan_vertical_bottom(game, map, i + 1, j);
		}
	}
}

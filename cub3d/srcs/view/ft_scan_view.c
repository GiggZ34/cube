/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:25:29 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 12:59:57 by grivalan         ###   ########lyon.fr   */
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
		file->error_code = ft_wall_to_view(game, &game->lst_walls_left, pos, 'L');
	}
	if (map[i][j] == '2' && ft_ennemy_to_list(game, j, i))
		file->error_code = 3;
	ft_scan_view(game, map, j, i);
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
		file->error_code = ft_wall_to_view(game, &game->lst_walls_top, pos, 'T');
	}
	if (map[i][j] == '2' && ft_ennemy_to_list(game, j, i))
		file->error_code = 3;
	ft_scan_view(game, map, j, i);
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
		file->error_code = ft_wall_to_view(game, &game->lst_walls_right, pos, 'R');
	}
	if (map[i][j] == '2' && ft_ennemy_to_list(game, j, i))
		file->error_code = 3;
	ft_scan_view(game, map, j, i);
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
		file->error_code = ft_wall_to_view(game, &game->lst_walls_bottom, pos, 'B');
	}
	if (map[i][j] == '2' && ft_ennemy_to_list(game, j, i))
		file->error_code = 3;
	ft_scan_view(game, map, j, i);
}

void		ft_scan_view(t_game *game, char **map, int x, int y)
{
	if (!game->file->error_code)
	{
		if ((map[y][x] != 'c' && map[y][x] != '1')
			&& (((x >= game->player->view.extremity[0].x)
			&& (x <= game->player->view.extremity[1].x))
			|| ((y >= game->player->view.extremity[0].y)
			&& (y <= game->player->view.extremity[1].y))))
		{
			map[y][x] = 'c';
			ft_scan_vertical_top(game, map, y - 1, x);
			ft_scan_vertical_bottom(game, map, y + 1, x);
			ft_scan_horizontal_left(game, map, y, x - 1);
			ft_scan_horizontal_right(game, map, y, x + 1);
		}
	}
}

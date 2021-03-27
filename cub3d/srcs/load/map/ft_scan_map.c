/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:30:41 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:47:25 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_scan_horizontal_left(t_game *game, char **map, int i, int j)
{
	int			pos[2];

	if (map[i][j] == '1')
	{
		pos[0] = j + 1;
		pos[1] = i;
		ft_create_plane(game, &game->lst_planes_left, pos, 'L');
	}
	else if (map[i][j] == '2')
		ft_init_ennemy(game, j, i);
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_vertical_top(t_game *game, char **map, int i, int j)
{
	int			pos[2];

	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i + 1;
		ft_create_plane(game, &game->lst_planes_top, pos, 'T');
	}
	else if (map[i][j] == '2')
		ft_init_ennemy(game, j, i);
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_horizontal_right(t_game *game, char **map, int i, int j)
{
	int			pos[2];

	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i;
		ft_create_plane(game, &game->lst_planes_right, pos, 'R');
	}
	if (map[i][j] == '2')
		ft_init_ennemy(game, j, i);
	ft_scan_map(game, map, i, j);
}

static void	ft_scan_vertical_bottom(t_game *game, char **map, int i, int j)
{
	int			pos[2];

	if (map[i][j] == '1')
	{
		pos[0] = j;
		pos[1] = i;
		ft_create_plane(game, &game->lst_planes_bottom, pos, 'B');
	}
	else if (map[i][j] == '2')
		ft_init_ennemy(game, j, i);
	ft_scan_map(game, map, i, j);
}

void		ft_scan_map(t_game *game, char **map, int i, int j)
{
	if (((i == ft_count_array(map) || j == (int)ft_strlen(map[i])
			|| i == 0 || j == 0) && map[i][j] != '1')
			|| ft_in_array(map[i][j], "012cNSEW") == -1)
		ft_trash_game(game, map_not_close, game->file.fd, ft_search_error(&game->file.map[i], j, i));
	else if (ft_in_array(map[i][j], "02NSEW") != -1)
	{
		map[i][j] = 'c';
		ft_scan_horizontal_left(game, map, i, j - 1);
		ft_scan_horizontal_right(game, map, i, j + 1);
		ft_scan_vertical_top(game, map, i - 1, j);
		ft_scan_vertical_bottom(game, map, i + 1, j);
	}
}

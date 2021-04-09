/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:30:41 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/07 14:06:39 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_light(t_game *game, int x, int y)
{
	t_light	*light;
	t_light	*tmp;

	light = ft_calloc(sizeof(t_light), 1);
	light->type = 'L';
	light->x = x + 0.5;
	light->y = y + 0.5;
	light->z = 0.7;
	light->rgb[0] = game->file.light_color[0];
	light->rgb[1] = game->file.light_color[1];
	light->rgb[2] = game->file.light_color[2];
	light->ratio = 0.3;
//	light->t = game->file.texture_light;
//	light->height = light->t->height;
//	light->width = light->t->size_line
//		/ light->height * light->ratio;
//	light->height = light->ratio;
	if (!game->light)
		game->light = light;
	else
	{
		tmp = game->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
}

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
	else if (map[i][j] == 'L')
		ft_init_light(game, j, i);
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
	else if (map[i][j] == 'L')
		ft_init_light(game, j, i);
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
	else if (map[i][j] == 'L')
		ft_init_light(game, j, i);
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
	else if (map[i][j] == 'L')
		ft_init_light(game, j, i);
	ft_scan_map(game, map, i, j);
}

void		ft_scan_map(t_game *game, char **map, int i, int j)
{
	if (((i == ft_count_array(map) || j == (int)ft_strlen(map[i])
			|| i == 0 || j == 0) && map[i][j] != '1')
			|| ft_in_array(map[i][j], "012cNSEWL") == -1)
		ft_trash_game(game, map_not_close, game->file.fd, ft_search_error(&game->file.map[i], j, i));
	else if (ft_in_array(map[i][j], "02NSEWL") != -1)
	{
		map[i][j] = 'c';
		ft_scan_horizontal_left(game, map, i, j - 1);
		ft_scan_horizontal_right(game, map, i, j + 1);
		ft_scan_vertical_top(game, map, i - 1, j);
		ft_scan_vertical_bottom(game, map, i + 1, j);
	}
}

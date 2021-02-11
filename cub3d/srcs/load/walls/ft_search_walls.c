/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:48:39 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 13:07:08 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dot	ft_search_border(char **map, t_dot position, int y, int x)
{
	while (map[(int)position.y][(int)position.x] != '1')
	{
		map[(int)position.y][(int)position.x] = 'c';
		position.x += x;
		position.y += y;
	}
	return (position);
}

static t_dot	ft_corner_border_right(char **map, t_player *player, double angle)
{
	if ((angle >= -45 && angle < 0) || (angle >= 315 && angle < 360))
		return (ft_search_border(map, player->position, -1, 0));
	else if (angle >= 0 && angle < 45)
		return (ft_search_border(map, player->position, -1, 1));
	else if (angle >= 45 && angle < 90)
		return (ft_search_border(map, player->position, 0, 1));
	else if (angle >= 90 && angle < 135)
		return (ft_search_border(map, player->position, 1, 1));
	else if (angle >= 135 && angle < 180)
		return (ft_search_border(map, player->position, 1, 0));
	else if (angle >= 180 && angle < 225)
		return (ft_search_border(map, player->position, 1, -1));
	else if (angle >= 225 && angle < 270)
		return (ft_search_border(map, player->position, 0, -1));
	else if (angle >= 270 && angle < 315)
		return (ft_search_border(map, player->position, -1, -1));
	return (player->position);
}

static t_dot	ft_corner_border_left(char **map, t_player *player, double angle)
{
	if ((angle >= -45 && angle < 0) || (angle >= 315 && angle < 360))
		return (ft_search_border(map, player->position, 0, -1));
	else if (angle >= 0 && angle < 45)
		return (ft_search_border(map, player->position, -1, -1));
	else if (angle >= 45 && angle < 90)
		return (ft_search_border(map, player->position, -1, 0));
	else if (angle >= 90 && angle < 135)
		return (ft_search_border(map, player->position, -1, 1));
	else if (angle >= 135 && angle < 180)
		return (ft_search_border(map, player->position, 0, 1));
	else if (angle >= 180 && angle < 225)
		return (ft_search_border(map, player->position, 1, 1));
	else if (angle >= 225 && angle < 270)
		return (ft_search_border(map, player->position, 1, 0));
	else if (angle >= 270 && angle < 315)
		return (ft_search_border(map, player->position, 1, -1));
	return (player->position);
}

static void		ft_scan_angle_view(t_game *game, char **map, t_player *player, double angle)
{
	if ((angle >= -45 && angle < 0) || (angle >= 315 && angle < 360))
		ft_scan_view(game, map, player->position.x - 1, player->position.y - 1);
	else if (angle >= 0 && angle < 45)
		ft_scan_view(game, map, player->position.x, player->position.y - 1);
	else if (angle >= 45 && angle < 90)
		ft_scan_view(game, map, player->position.x + 1, player->position.y - 1);
	else if (angle >= 90 && angle < 135)
		ft_scan_view(game, map, player->position.x + 1, player->position.y);
	else if (angle >= 135 && angle < 180)
		ft_scan_view(game, map, player->position.x + 1, player->position.y + 1);
	else if (angle >= 180 && angle < 225)
		ft_scan_view(game, map, player->position.x, player->position.y + 1);
	else if (angle >= 225 && angle < 270)
		ft_scan_view(game, map, player->position.x - 1, player->position.y + 1);
	else if (angle >= 270 && angle < 315)
		ft_scan_view(game, map, player->position.x - 1, player->position.y);
}

int				ft_search_walls(t_game *game)
{
	char	**map;
	t_dot	min;
	t_dot	max;

	if (!(map = ft_map_cpy(game->file->map, game->file->height_map)))
		return (game->file->error_code = 3);
	min = ft_corner_border_left(map, game->player, game->player->angle);
	max = ft_corner_border_right(map, game->player, game->player->angle);
	game->player->view.extremity[0].x = ft_min(min.x, max.x);
	game->player->view.extremity[1].x = ft_max(min.x, max.x);
	game->player->view.extremity[0].y = ft_min(min.y, max.y);
	game->player->view.extremity[1].y = ft_max(min.y, max.y);
	ft_scan_angle_view(game, map, game->player, game->player->angle);
	ft_free_array(map);
	return (0);
}

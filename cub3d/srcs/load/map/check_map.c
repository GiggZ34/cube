/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:58:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 18:17:45 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_start_pos(t_game *game, int *row, int *col)
{
	int	nb_pos;
	int	i;
	int	j;

	nb_pos = 0;
	i = -1;
	while (game->file.map[++i])
	{
		j = -1;
		while (game->file.map[i][++j])
		{
			if (ft_in_array(game->file.map[i][j], "NSEW") != -1)
			{
				nb_pos++;
				*row = i;
				*col = j;
			}
		}
	}
	if (nb_pos > 1)
		return (ft_trash_game(game, no_s_position, -1, "\n"));
	else if (!nb_pos)
		return (ft_trash_game(game, mult_s_position, -1, "\n"));
	return (0);
}

int	ft_check_map(t_game *game, t_file *file)
{
	char		**map_check;
	int			pos[2];

	game->file.height_map = ft_count_array(file->map);
	pos[0] = 0;
	pos[1] = 0;
	map_check = ft_map_cpy(game->file.map, game->file.height_map);
	if (!(map_check))
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	if (ft_start_pos(game, &pos[0], &pos[1]) == 0)
	{
		ft_scan_map(game, map_check, pos[0], pos[1]);
		ft_free_array(map_check);
		ft_init_player(game, pos[1], pos[0], file->map[pos[0]][pos[1]]);
		ft_lst_planes_to_tab(game);
	}
	return (0);
}

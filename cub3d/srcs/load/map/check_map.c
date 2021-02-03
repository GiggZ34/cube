/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:58:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 15:58:56 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_start_pos(t_file *file, int *row, int *col)
{
	int nb_pos;
	int i;
	int j;

	nb_pos = 0;
	i = -1;
	while (file->map[++i])
	{
		j = -1;
		while (file->map[i][++j])
			if (ft_in_array(file->map[i][j], "NSEW") != -1)
			{
				nb_pos++;
				*row = i;
				*col = j;
			}
	}
	if (nb_pos > 1)
		ft_error_file(file, 4, file->map[*row]);
	else if (nb_pos == 0)
		ft_error_file(file, 4, "No position");
	return (file->error_code);
}

void			del(void *content)
{
	free(content);
}

int				ft_check_map(t_game *game, t_file *file)
{
	char		**map_check;
	int			pos[2];

	file->height_map = ft_count_array(file->map);
	if (!(map_check = ft_map_cpy(file->map, file->height_map)))
		return (-3);
	if (ft_start_pos(file, &pos[0], &pos[1]) == 0)
	{
		ft_scan_map(game, map_check, pos[0], pos[1]);
		ft_free_array(map_check);
		 if (!(game->player = ft_init_player(game, pos[1], pos[0], file->map[pos[0]][pos[1]])))
		 	return (file->error_code = 3);
		if (file->error_code == 0 && ft_create_walls(&game->lst_walls_bottom))
			return (file->error_code = 3);
		if (file->error_code == 0 && ft_create_walls(&game->lst_walls_top))
			return (file->error_code = 3);
		if (file->error_code == 0 && ft_create_walls(&game->lst_walls_right))
			return (file->error_code = 3);
		if (file->error_code == 0 && ft_create_walls(&game->lst_walls_left))
			return (file->error_code = 3);
		if ((ft_search_walls(game)))
			return (file->error_code = 3);
		if ((ft_init_tab_vector(game, game->player->view.view)))
			return (file->error_code = 3);
	}
	return (file->error_code);
}

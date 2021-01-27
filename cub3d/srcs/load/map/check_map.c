/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:58:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/26 15:35:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		**ft_map_cpy(char **map)
{
	char	**new_map;
	int		len;
	int		i;

	if (!map)
		return (0);
	len = ft_count_array(map);
	if (!(new_map = ft_calloc(sizeof(char**), len + 1)))
		return (0);
	i = -1;
	while (map[++i])
		new_map[i] = ft_strdup(map[i]);
	return (new_map);
}

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
	int			row;
	int			col;
	t_player	*player;

	if (!(map_check = ft_map_cpy(file->map)))
		return (-3);
	if (ft_start_pos(file, &row, &col) == 0)
	{
		ft_scan_map(game, map_check, row, col);
		if (file->error_code == 0)
			ft_modif_map(game, map_check);
		t_list	*l;
		t_plane	*w;
		l = game->lst_planes;
		while (l)
		{
			w = l->content;
			printf("%d | %d | %d\n", (int)w->a, (int)w->b, (int)w->d);
		}
		if (ft_start_pos(file, &row, &col) == 0)
		{
			player = ft_init_player(game, col, row, file->map[row][col]);
			game->player = player;
			ft_scan_map(game, file->map, row, col);
		}
		if (file->error_code == 0)
			ft_create_walls(game->lst_planes, game);
	}
	ft_free_array(map_check);
	exit(0);
	return (file->error_code);
}

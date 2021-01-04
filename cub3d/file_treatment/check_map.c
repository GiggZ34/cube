/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:58:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/02 15:29:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**ft_map_cpy(char **map)
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

static void	ft_scan_map(t_file *file, char **map, int i, int j)
{
	if(!file->error_code)
	{
		if (map[i][j] == '1')
			map[i][j] = 'm';
		if ((((i == ft_count_array(map) || j == ft_strlen(map[i]))
				|| (i == 0 || j == 0)) && map[i][j] != 'm')
				|| ft_in_array(map[i][j], "02cm") == -1)
			ft_error_file(file, 2, ft_search_error(&file->map[i], j, i));
		else if ((i > 0 && i < ft_count_array(map))
				&& (j > 0 && j < ft_strlen(map[i]))
				&& (map[i][j] != 'm' && map[i][j] != 'c'))
		{
			map[i][j] = 'c';
			ft_scan_map(file, map, i - 1, j - 1);
			ft_scan_map(file, map, i - 1, j);
			ft_scan_map(file, map, i - 1, j + 1);
			ft_scan_map(file, map, i, j - 1);
			ft_scan_map(file, map, i, j + 1);
			ft_scan_map(file, map, i + 1, j - 1);
			ft_scan_map(file, map, i + 1, j);
			ft_scan_map(file, map, i + 1, j + 1);
		}
	}
}

static int	ft_start_pos(t_file *file, int *row, int *col)
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
			if(ft_in_array(file->map[i][j], "NSEW") != -1)
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

int			ft_check_map(t_file *file)
{
	char	**map_check;
	int		row;
	int		col;

	if (!(map_check = ft_map_cpy(file->map)))
		return (-3);
	if (ft_start_pos(file, &row, &col) == 0)
	{
		map_check[row][col] = '0';
		ft_scan_map(file, map_check, row, col);
		if (file->error_code == 0)
			ft_modif_map(file, map_check);
	}
	ft_free_array(map_check);
	return (file->error_code);
}

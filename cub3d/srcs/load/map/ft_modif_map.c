/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:45:44 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/23 14:47:49 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_delete_difference(t_file *file, char **map_checked)
{
	int i;
	int j;

	i = -1;
	while (file->map[++i])
	{
		j = -1;
		while (file->map[i][++j])
			if (file->map[i][j] == map_checked[i][j])
				file->map[i][j] = ' ';
	}
}

static int	*ft_check_empty_line(t_file *file, int nb_row, int *min)
{
	int	*tab;
	int i;
	int j;

	if (!(tab = ft_calloc(sizeof(int), nb_row)))
		return (0);
	*min = -1;
	i = -1;
	while (file->map && file->map[++i])
	{
		j = 0;
		while (file->map[i][j] && file->map[i][j] == ' ')
			j++;
		if (file->map[i][j])
		{
			tab[i] = j;
			if (*min == -1 || tab[i] < *min)
				*min = tab[i];
		}
		else
			tab[i] = -1;
	}
	return (tab);
}

static char	**ft_map_generate(t_file *file, int nb_row, int min, int *tab)
{
	char	**new_map;
	char	*line;
	int		size;
	int		i;

	new_map = 0;
	i = -1;
	while (!file->error_code && ++i < nb_row)
		if (tab[i] != -1)
		{
			size = ft_strlen(file->map[i]);
			while (file->map[i][size - 1] == ' ')
				size--;
			size -= min;
			if (!(line = ft_substr(file->map[i], min, size)))
				ft_error_file(file, 3, "in function ft_map_generate");
			if (!(new_map = ft_generate_map(new_map, line)))
				ft_error_file(file, 3, "in function ft_map_generate");
		}
	return (new_map);
}

static int	ft_new_map(t_file *file, int nb_row)
{
	char	**new_map;
	int		*tab;
	int		min;

	if (!(tab = ft_check_empty_line(file, nb_row, &min)))
		ft_error_file(file, 3, "in function ft_new_map");
	if (min == 0 || !tab)
	{
		free(tab);
		return (file->error_code);
	}
	if (!(new_map = ft_map_generate(file, nb_row, min, tab)))
		ft_error_file(file, 3, "in function ft_new_map");
	if (!file->error_code)
	{
		ft_free_array(file->map);
		file->map = new_map;
	}
	else
		ft_free_array(new_map);
	free(tab);
	return (file->error_code);
}

int			ft_modif_map(t_game *game, char **map_checked)
{
	int	nb_row;

	ft_delete_difference(game->file, map_checked);
	if (!(nb_row = ft_count_array(game->file->map)))
		ft_error_file(game->file, 3, "in function ft_modif_map");
	if (game->file->error_code == 0)
		ft_new_map(game->file, nb_row);
	return (game->file->error_code);
}

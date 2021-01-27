/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/20 09:26:39 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_three_parameter(t_file *file, char **array)
{
	int len;

	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
	{
		file->ground_color = ft_color_generate(ft_atoi(array[1]),
									ft_atoi(array[2]), ft_atoi(array[3]), 0);
	}
	else if (!ft_strncmp(*array, "C", len))
	{
		file->sky_color = ft_color_generate(ft_atoi(array[1]),
									ft_atoi(array[2]), ft_atoi(array[3]), 0);
	}
	else
		return (5);
	return (0);
}

static int		ft_two_parameter(t_game *game, char **array)
{
	int len;

	len = ft_strlen(*array);
	if (!game->screen && !ft_strncmp(*array, "R", len))
	{
		if (!(game->screen = ft_calloc(sizeof(t_screen), 1)))
			return (3);
		game->screen->width = ft_atoi(array[1]);
		game->screen->height = ft_atoi(array[2]);
	}
	else
		return (5);
	return (0);
}

static int		ft_one_parameter(void *mlx, t_file *file, char **array)
{
	char	*link;
	size_t	len;

	len = ft_strlen(*array);
	if (!(link = ft_strdup(array[1])))
		return (-3);
	if (!ft_strncmp(*array, "NO", 2))
		file->error_code = ft_img_generate(mlx, file, array[1], "NO");
	else if (!ft_strncmp(*array, "SO", 2))
		file->error_code = ft_img_generate(mlx, file, array[1], "SO");
	else if (!ft_strncmp(*array, "WE", 2))
		file->error_code = ft_img_generate(mlx, file, array[1], "WE");
	else if (!ft_strncmp(*array, "EA", 2))
		file->error_code = ft_img_generate(mlx, file, array[1], "EA");
	else if (!ft_strncmp(*array, "S", 1))
		file->error_code = ft_img_generate(mlx, file, array[1], "S");
	else
		return (5);
	return (file->error_code);
}

int				ft_file_to_struct(t_game *game, t_file *file, char *line)
{
	char	**array;
	int		count;

	if (!(array = ft_split(line, "\t ,")))
	{
		file->error_code = 3;
		return (file->error_code);
	}
	if ((count = ft_count_array(array)) == 2)
		file->error_code = ft_one_parameter(game->mlx, file, array);
	else if (count == 3)
		file->error_code = ft_two_parameter(game, array);
	else if (count == 4)
		file->error_code = ft_three_parameter(file, array);
	else
		file->error_code = 5;
	ft_free_array(array);
	if (file->error_code)
		ft_error_file(file, file->error_code, line);
	return (file->error_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/02 12:46:03 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		ft_three_parameter(t_file *file, char **array)
{
	int len;

	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
	{
		file->ground = 'F';
		file->ground_color[0] = ft_atoi(array[1]);
		file->ground_color[1] = ft_atoi(array[2]);
		file->ground_color[2] = ft_atoi(array[3]);
	}
	else if (!ft_strncmp(*array, "C", len))
	{
		file->sky = 'C';
		file->sky_color[0] = ft_atoi(array[1]);
		file->sky_color[1] = ft_atoi(array[2]);
		file->sky_color[2] = ft_atoi(array[3]);
	}
	else
		return (5);
	return (0);
}

static int		ft_two_parameter(t_file *file, char **array)
{
	int len;

	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "R", len))
	{
		file->resolution = 'R';
		file->resolution_x = ft_atoi(array[1]);
		file->resolution_y = ft_atoi(array[2]);
	}
	else
		return (5);
	return (0);
}

static int		ft_one_parameter(t_file *file, char **array)
{
	char	*link;
	size_t	len;

	len = ft_strlen(*array);
	if (!(link = ft_strdup(array[1])))
		return (-3);
	if (!file->north_texture && !ft_strncmp(*array, "NO", len))
		file->north_texture = link;
	else if (!file->south_texture && !ft_strncmp(*array, "SO", len))
		file->south_texture = link;
	else if (!file->west_texture && !ft_strncmp(*array, "WE", len))
		file->west_texture = link;
	else if (!file->east_texture && !ft_strncmp(*array, "EA", len))
		file->east_texture = link;
	else if (!file->sprite_texture && !ft_strncmp(*array, "S", len))
		file->sprite_texture = link;
	else
	{
		free(link);
		return (5);
	}
	return (0);
}

int			ft_file_to_struct(t_file *file, char *line)
{
	char	**array;
	int		count;

	if (!(array = ft_split(line, "\t ,")))
	{
		file->error_code = 3;
		return (file->error_code);
	}
	count = ft_count_array(array);
	if (count == 2)
		file->error_code = ft_one_parameter(file, array);
	else if (count == 3)
		file->error_code = ft_two_parameter(file, array);
	else if (count == 4)
		file->error_code = ft_three_parameter(file, array);
	else
		ft_error_file(file, 5, line);
	ft_free_array(array);
	if (file->error_code)
		ft_error_file(file, file->error_code, line);
	return (file->error_code);
}

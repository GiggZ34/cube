/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 17:05:07 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_change_resolution(t_game *game, int fd)
{
	int	width_screen;
	int	height_screen;

	if (mlx_get_screen_size(game->mlx, &width_screen, &height_screen) == -1)
		return (ft_trash_game(game, crash_mlx_function, fd));
	if (game->screen.width > width_screen)
		game->screen.width = width_screen;
	if (game->screen.height > height_screen)
		game->screen.height = height_screen;
	return (0);
}

static int		ft_three_parameter(t_game *game, char **array, int fd)
{
	int	len;
	int	r;
	int	g;
	int	b;

	r = ft_atoi(array[1]);
	g = ft_atoi(array[2]);
	b = ft_atoi(array[3]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_trash_game(game, incorrect_color_code, fd));
	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
		game->file.ground_color = ft_color_generate(r, g, b, 0);
	else if (!ft_strncmp(*array, "C", len))
		game->file.sky_color = ft_color_generate(r, g, b, 0);
	else
		return (ft_trash_game(game, unknow_instruction, fd));
	return (0);
}

static int		ft_two_parameter(t_game *game, char **array, int fd)
{
	int			len;
	long long	size;

	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "R", len))
	{
		size = ft_atoi(array[1]);
		if (size > 0 && size <= INT_MAX)
			game->screen.width = size;
		else
			return (ft_trash_game(game, incorrect_resolution_size, fd));
		size = ft_atoi(array[2]);
		if (size > 0 && size <= INT_MAX)
			game->screen.height = size;
		else
			return (ft_trash_game(game, incorrect_resolution_size, fd));
		ft_change_resolution(game, fd);
	}
	else
		return (ft_trash_game(game, unknow_instruction, fd));
	if (!(game->window = mlx_new_window(game->mlx,
						game->screen.width, game->screen.height, "Cub3D")))
		return (ft_trash_game(game, win_creation_fail, 1));
	return (0);
}

static int		ft_one_parameter(t_game *game, char **array, int fd)
{
	char	*link;
	if (!(link = ft_strdup(array[1])))
		return (ft_trash_game(game, allocation_fail, fd));
	if (!ft_strncmp(*array, "NO", 2))
		ft_img_generate(game, array[1], "NO");
	else if (!ft_strncmp(*array, "SO", 2))
		ft_img_generate(game, array[1], "SO");
	else if (!ft_strncmp(*array, "WE", 2))
		ft_img_generate(game, array[1], "WE");
	else if (!ft_strncmp(*array, "EA", 2))
		ft_img_generate(game, array[1], "EA");
	else if (!ft_strncmp(*array, "S", 1))
		ft_img_generate(game, array[1], "S");
	else
		return (ft_trash_game(game, unknow_instruction, fd));
	free(link);
	return (0);
}

int				ft_file_to_struct(t_game *game, char *line, int fd)
{
	char	**array;
	int		count;

	if (!(array = ft_split(line, "\t ,")))
		return (ft_trash_game(game, allocation_fail, fd));
	if ((count = ft_count_array(array)) == 2)
		ft_one_parameter(game, array, fd);
	else if (count == 3)
		ft_two_parameter(game, array, fd);
	else if (count == 4)
		ft_three_parameter(game, array, fd);
	else
		return (ft_trash_game(game, unknow_instruction, fd));
	ft_free_array(array);
	return (0);
}

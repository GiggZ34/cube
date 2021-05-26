/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 17:00:04 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_three_parameter(t_game *game, char **array, int fd)
{
	int	len;
	int	rgb[3];

	rgb[0] = ft_atoi(array[1]);
	rgb[1] = ft_atoi(array[2]);
	rgb[2] = ft_atoi(array[3]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
	{
		ft_free_array(array);
		ft_trash_game(game, incorrect_color_code, fd, "");
	}
	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
		game->file.ground_color = ft_color_generate(rgb[0], rgb[1], rgb[2], 0);
	else if (!ft_strncmp(*array, "C", len))
		game->file.sky_color = ft_color_generate(rgb[0], rgb[1], rgb[2], 0);
	else if (!ft_strncmp(*array, "L", len))
		init_color_light(game, rgb[0], rgb[1], rgb[2]);
	else
	{
		ft_free_array(array);
		ft_trash_game(game, unknow_instruction, fd, "argument not found");
	}
}

static int	init_res(long long res_file, int res_max)
{
	if (res_file <= 0)
		return (0);
	if (res_file > res_max)
		return (res_max);
	return (res_file);
}

static void	ft_two_parameter(t_game *game, char **array, int fd)
{
	mlx_get_screen_size(game->mlx, &game->screen.max_x, &game->screen.max_y);
	if (!ft_strncmp(*array, "R", ft_strlen(*array)))
	{
		game->screen.width = init_res(ft_atoi(array[1]), game->screen.max_x);
		game->screen.height = init_res(ft_atoi(array[2]), game->screen.max_y);
	}
	else
	{
		ft_free_array(array);
		ft_trash_game(game, unknow_instruction, fd, "Argument not found");
	}
	if (game->screen.width <= 0 || game->screen.height <= 0)
	{
		ft_free_array(array);
		ft_trash_game(game, win_creation_fail, fd, "Resolution invalid");
	}
	if (!game->save_picture)
		game->window = mlx_new_window(game->mlx,
				game->screen.width, game->screen.height, "cub3d");
	if (!game->save_picture && !game->window)
	{
		ft_free_array(array);
		ft_trash_game(game, win_creation_fail, fd, "In ft_two_parameter");
	}
}

static void	ft_one_parameter(t_game *game, char **array, int fd)
{
	char	*link;

	link = ft_strdup(array[1]);
	if (!link)
		ft_trash_game(game, allocation_fail, fd, "In ft_one_parameter");
	if (!ft_strncmp(*array, "NO\0", 3))
		ft_img_generate(game, array[1], "NO");
	else if (!ft_strncmp(*array, "SO\0", 3))
		ft_img_generate(game, array[1], "SO");
	else if (!ft_strncmp(*array, "WE\0", 3))
		ft_img_generate(game, array[1], "WE");
	else if (!ft_strncmp(*array, "EA\0", 3))
		ft_img_generate(game, array[1], "EA");
	else if (!ft_strncmp(*array, "S\0", 2))
		ft_img_generate(game, array[1], "S");
	else if (!ft_strncmp(*array, "C\0", 2))
		ft_img_generate(game, array[1], "C");
	else if (!ft_strncmp(*array, "F\0", 2))
		ft_img_generate(game, array[1], "F");
	else
	{
		ft_free_array(array);
		ft_trash_game(game, unknow_instruction, fd, "");
	}
	free(link);
}

int	ft_file_to_struct(t_game *game, char *line, int fd)
{
	char	**array;
	int		count;

	if (!check_format(game, line, &array))
		ft_trash_game(game, allocation_fail, fd, "In check_format");
	count = ft_count_array(array);
	if (count == 2)
		ft_one_parameter(game, array, fd);
	else if (count == 3)
		ft_two_parameter(game, array, fd);
	else if (count == 4)
		ft_three_parameter(game, array, fd);
	else
		ft_trash_game(game, unknow_instruction, fd, "Argument not exist");
	ft_free_array(array);
	return (0);
}

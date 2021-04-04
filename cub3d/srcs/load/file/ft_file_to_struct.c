/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 19:33:11 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_three_parameter(t_game *game, char **array, int fd)
{
	int	len;
	int	r;
	int	g;
	int	b;

	r = ft_atoi(array[1]);
	g = ft_atoi(array[2]);
	b = ft_atoi(array[3]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_array(array);
		ft_trash_game(game, incorrect_color_code, fd, "Color incorrect");
	}
	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
		game->file.ground_color = ft_color_generate(r, g, b, 0);
	else if (!ft_strncmp(*array, "C", len))
		game->file.sky_color = ft_color_generate(r, g, b, 0);
	else if (!ft_strncmp(*array, "L", len))
		game->file.light_color = ft_color_generate(r, g, b, 0);
	else
	{
		ft_free_array(array);
		ft_trash_game(game, unknow_instruction, fd, "argument not found");
	}
	return (0);
}

static int	ft_two_parameter(t_game *game, char **array, int fd)
{
	int			len;
	long long	size;

	mlx_get_screen_size(game->mlx, &game->screen.max_x, &game->screen.max_y);
	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "R", len))
	{
		size = ft_atoi(array[1]);
		if (size <= game->screen.max_x)
			game->screen.width = size;
		else
			game->screen.width = game->screen.max_x;
		size = ft_atoi(array[2]);
		if (size <= game->screen.max_y)
			game->screen.height = size;
		else
			game->screen.height = game->screen.max_y;
	}
	else
	{
		ft_free_array(array);
		ft_trash_game(game, unknow_instruction, fd, "Argument not found");
	}
	if (game->screen.width == 0 || game->screen.height == 0)
	{
		ft_free_array(array);
		ft_trash_game(game, win_creation_fail, fd, "Resolution a 0.");
	}
	if (!game->save_picture)
		game->window = mlx_new_window(game->mlx,
				game->screen.width, game->screen.height, "Cub3D");
	if (!game->save_picture && !game->window)
	{
		ft_free_array(array);
		ft_trash_game(game, win_creation_fail, fd, "In ft_two_parameter");
	}
	return (0);
}

static int	ft_one_parameter(t_game *game, char **array, int fd)
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
	else if (!ft_strncmp(*array, "L\0", 2))
		ft_img_generate(game, array[1], "LI");
	else
		ft_img_generate(game, array[1], ft_strdup(array[0]));
	free(link);
	return (0);
}

void	ft_add_arguments(t_game *game, t_file *file, char *arg)
{
	t_list	*lst;
	t_list	*new_list;
	char	*test;
	char	*content;

	lst = file->check_file;
	while (lst)
	{
		test = lst->content;
		if (!ft_strncmp(test, arg, 2))
			ft_trash_game(game, arguments_error, file->fd, "This arg exist");
		lst = lst->next;
	}
	content = ft_strdup(arg);
	if (!content)
		ft_trash_game(game, allocation_fail, file->fd, "In ft_add_arguments");
	new_list = ft_lstnew(content);
	if (!new_list)
	{
		free(content);
		ft_trash_game(game, allocation_fail, file->fd, "In ft_add_arguments");
	}
	ft_lstadd_back(&(game->file.check_file), new_list);
}

int	ft_file_to_struct(t_game *game, char *line, int fd)
{
	char	**array;
	int		count;

	if (!check_format(line, &array))
		ft_trash_game(game, allocation_fail, fd, "In check_format");
	ft_add_arguments(game, &game->file, array[0]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:58 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:43:09 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_change_resolution(t_game *game, int fd)
{
	int	width_screen;
	int	height_screen;

	if (mlx_get_screen_size(game->mlx, &width_screen, &height_screen) == -1)
		return (ft_trash_game(game, crash_mlx_function, fd, "Function ft_change_resolution | line 20\n"));
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
		return (ft_trash_game(game, incorrect_color_code, fd, "Color incorrect\n"));
	len = ft_strlen(*array);
	if (!ft_strncmp(*array, "F", len))
		game->file.ground_color = ft_color_generate(r, g, b, 0);
	else if (!ft_strncmp(*array, "C", len))
		game->file.sky_color = ft_color_generate(r, g, b, 0);
	else
		return (ft_trash_game(game, unknow_instruction, fd, "argument not found\n"));
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
			return (ft_trash_game(game, incorrect_resolution_size, fd, "Resolution invalide\n"));
		size = ft_atoi(array[2]);
		if (size > 0 && size <= INT_MAX)
			game->screen.height = size;
		else
			return (ft_trash_game(game, incorrect_resolution_size, fd, "Resolution invalide\n"));
		ft_change_resolution(game, fd);
	}
	else
		return (ft_trash_game(game, unknow_instruction, fd, "Argument not found\n"));
	if (!(game->window = mlx_new_window(game->mlx,
						game->screen.width, game->screen.height, "Cub3D")))
		return (ft_trash_game(game, win_creation_fail, fd, "Function ft_two_parameter | line 73\n"));
	return (0);
}

static int		ft_one_parameter(t_game *game, char **array, int fd)
{
	char	*link;
	if (!(link = ft_strdup(array[1])))
		return (ft_trash_game(game, allocation_fail, fd, "Function ft_one_parameter | line 82\n"));
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
	else
		return (ft_trash_game(game, unknow_instruction, fd, "Argument not found\n"));
	free(link);
	return (0);
}

void			ft_add_arguments(t_game *game, t_file *file, char *arg)
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
			ft_trash_game(game, arguments_error, file->fd, "This argument exist\n");
		lst = lst->next;
	}
	content = ft_strdup(arg);
	if (!content)
		ft_trash_game(game, allocation_fail, file->fd, "Function ft_add_arguments | line 115\n");
	new_list = ft_lstnew(content);
	if (!new_list)
	{
		free(content);
		ft_trash_game(game, allocation_fail, file->fd, "Function ft_add_arguments | line 118\n");
	}
	ft_lstadd_back(&(game->file.check_file), new_list);
}

int				ft_file_to_struct(t_game *game, char *line, int fd)
{
	char	**array;
	int		count;

	if (!(array = ft_split(line, " ,")))
		return (ft_trash_game(game, allocation_fail, fd, "Function ft_file_to_struct | line 132\n"));
	ft_add_arguments(game, &game->file, array[0]);
	if ((count = ft_count_array(array)) == 2)
		ft_one_parameter(game, array, fd);
	else if (count == 3)
		ft_two_parameter(game, array, fd);
	else if (count == 4)
		ft_three_parameter(game, array, fd);
	else
		return (ft_trash_game(game, unknow_instruction, fd, "Argument not exist\n"));
	ft_free_array(array);
	return (0);
}

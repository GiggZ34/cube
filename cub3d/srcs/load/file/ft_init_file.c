/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:21:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 16:33:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	search_args(t_list *lst, char *arg)
{
	char	*str;
	int		size;

	size = ft_strlen(arg);
	while (lst)
	{
		str = lst->content;
		if (!ft_strncmp(str, arg, size))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static int	missing_args(t_game *game, t_list *lst)
{
	int	size_list;

	size_list = ft_lstsize(lst);
	if (size_list == 9)
		return (0);
	else if (size_list < 8)
		return (1);
	else
		if (search_args(lst, "L"))
			return (1);
	game->file.light_color[0] = 1;
	game->file.light_color[1] = 1;
	game->file.light_color[2] = 1;
	return (0);
}

static int	regex_file(t_game *game, const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len > 4 && s[len - 4] == '.' && s[len - 3] == 'c'
		&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (succes);
	return (ft_trash_game(game, file_incorrect, -1,
			"\033[31mExtension invalid\033[0m"));
}

int	ft_init_file(t_file *file, t_game *game, char *dir_file)
{
	regex_file(game, dir_file);
	if (open(dir_file, O_DIRECTORY) != -1)
		ft_trash_game(game, file_incorrect, -1,
			"\033[31mIt's directory\033[0m");
	file->fd = open(dir_file, O_RDONLY);
	if (file->fd <= 0)
		return (ft_trash_game(game, open_file_fail, file->fd, "\n"));
	printf("File :\t\t\033[35mvalid\033[0m\n");
	ft_parsing_file(game, file->fd);
	if (missing_args(game, game->file.check_file))
		ft_trash_game(game, arguments_error, -1, "missing args");
	printf("Arguments :\t\033[35mvalids\033[0m\n");
	ft_check_map(game, file);
	printf("Map :\t\t\033[35mvalid\033[0m\n");
	return (0);
}

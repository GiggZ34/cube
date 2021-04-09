/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:21:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/08 17:49:00 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	regex_file(t_game *game, const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len > 4 && s[len - 4] == '.' && s[len - 3] == 'c'
		&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (succes);
	return (ft_trash_game(game, file_incorrect, -1,
			"\033[31mExtension invalide\033[0m"));
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
	printf("File ---> \033[35mvalide\n\033[0m");
	ft_parsing_file(game, file->fd);
	ft_check_map(game, file);
	return (0);
}

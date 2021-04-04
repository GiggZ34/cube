/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:21:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 14:30:16 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		regex_file(t_game *game, const char *s)
{
	size_t len;

	len = ft_strlen(s);
	if (len > 4 && s[len - 4] == '.' && s[len - 3] == 'c'
				&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (succes);
	return (ft_trash_game(game, allocation_fail, -1, "\n"));
}

static void		ft_init_t_file(t_game *game)
{
	game->file.ground_color = -1;
	game->file.sky_color = -1;
	game->screen.width = -1;
	game->screen.height = -1;
}

int				ft_init_file(t_file *file, t_game *game, char *dir_file)
{
	ft_init_t_file(game);
	regex_file(game, dir_file);
	file->fd = open(dir_file, O_RDONLY);
	if (file->fd <= 0)
		return (ft_trash_game(game, open_file_fail, file->fd, "\n"));
	ft_parsing_file(game, file->fd);
	ft_check_map(game, file);
	return (0);
}

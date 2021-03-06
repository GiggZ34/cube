/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:21:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/02 14:46:38 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		regex_file(const char *s)
{
	size_t len;

	if ((len = ft_strlen(s)) > 4 && s[len - 4] == '.' && s[len - 3] == 'c'
				&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (1);
	return (0);
}

static void		ft_init_t_file(t_game *game)
{
	ft_bzero(game->file, sizeof(t_file));
	game->file->ground_color = -1;
	game->file->sky_color = -1;
	game->screen.width = -1;
	game->screen.height = -1;
}

int				ft_init_file(t_file *file, t_game *game, char *dir_file)
{
	int		error;
	int		fd;

	ft_init_t_file(game);
	if (!regex_file(dir_file))
		return (ft_clear_file(file, -1, ft_error_file(file, 7, dir_file)));
	if ((fd = open(dir_file, O_RDONLY)) == -1)
		return (ft_clear_file(file, fd, ft_error_file(file, 6, "")));
	if ((error = ft_parsing_file(game, fd, file)) != 0)
		return (ft_clear_file(file, fd, error));
	if ((error = ft_check_struct(game)) != 0)
		return (ft_clear_file(file, fd, error));
	game->window = mlx_new_window(game->mlx,
						game->screen.width, game->screen.height, "Cub3D");
	if ((error = ft_check_map(game, file)) != 0 && error != -1)
		return (ft_clear_file(file, fd, error));
	return (file->error_code);
}

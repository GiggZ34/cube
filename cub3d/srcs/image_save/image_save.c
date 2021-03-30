/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:00:33 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/30 11:38:48 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_bitmap_header(t_game *game, unsigned char **file, int size)
{
	(*file)[0] = (unsigned char)('B');
	(*file)[1] = (unsigned char)('M');
	(*file)[2] = (unsigned char)(size);
	(*file)[3] = (unsigned char)(size >> 8);
	(*file)[4] = (unsigned char)(size >> 16);
	(*file)[5] = (unsigned char)(size >> 24);
	(*file)[10] = (unsigned char)(14 + 40);
	(*file)[0 + 14] = (unsigned char)(40);
	(*file)[4 + 14] = (unsigned char)(game->screen.width >> 0);
	(*file)[5 + 14] = (unsigned char)(game->screen.width >> 8);
	(*file)[6 + 14] = (unsigned char)(game->screen.width >> 16);
	(*file)[7 + 14] = (unsigned char)(game->screen.width >> 24);
	(*file)[8 + 14] = (unsigned char)(game->screen.height >> 0);
	(*file)[9 + 14] = (unsigned char)(game->screen.height >> 8);
	(*file)[10 + 14] = (unsigned char)(game->screen.height >> 16);
	(*file)[11 + 14] = (unsigned char)(game->screen.height >> 24);
	(*file)[12 + 14] = (unsigned char)(1);
	(*file)[14 + 14] = (unsigned char)(game->screen.bit);
}

static int	create_file(t_game *game, unsigned char **file, int fd)
{
	unsigned int	size;

	size = game->screen.width * game->screen.height * 4;
	(*file) = ft_calloc(size + 54, 1);
	if (!(*file))
	{
		close(fd);
		return (ft_trash_game(game, allocation_fail, -1, "Fuction ft_header_create | line 17\n"));
	}
	create_bitmap_header(game, file, size);
	return (0);
}

static void	image_to_file(t_game *game, unsigned char *file)
{
	int				y;
	int				x;
	int				i;
	int				j;
	int				id;

	y = game->screen.height;
	j = 0;
	i = 0;
	while (--y >= 0)
	{
		x = -1;
		while (++x < game->screen.size)
		{
			id = y * game->screen.size + x;
			file[54 + i] = game->screen.color[id];
			file[54 + i + 1] = game->screen.color[id] >> 8;
			file[54 + i + 2] = game->screen.color[id] >> 16;
			file[54 + i + 3] = game->screen.color[id] >> 24;
			i += 4;
		}
		j++;
	}
}

char	*search_name(char **name)
{
	int i;
	int	fd;

	i = 0;
	fd = 1;
	while (1)
	{
		if (!file_name_gen(name, "./img_", i, ".bmp"))
			return (*name);
		fd = open(*name, O_RDONLY);
		if (fd == -1)
			return (*name);
		i++;
		free(*name);
		*name = NULL;
	}
}

size_t	ft_image_save(t_game *game)
{
	int				fd;
	unsigned char	*file;
	char			*name;
	size_t			size_file;

	if (!search_name(&name))
		return (ft_trash_game(game, open_file_fail, -1, "function ft_image_save\n"));
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (fd < 0)
		return (ft_trash_game(game, open_file_fail, -1, "function ft_image_save\n"));
	create_file(game, &file, fd);
	image_to_file(game, file);
	size_file = write(fd, file, game->screen.width * game->screen.height * 4 + 54);
	close(fd);
	return (size_file);
}

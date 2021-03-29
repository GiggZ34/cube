/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:00:33 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/29 19:01:19 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_create_bitmap_file_header(int file_size, unsigned char **file)
{
	(*file)[0] = (unsigned char)('B');
	(*file)[1] = (unsigned char)('M');
	(*file)[2] = (unsigned char)(file_size);
	(*file)[3] = (unsigned char)(file_size >> 8);
	(*file)[4] = (unsigned char)(file_size >> 16);
	(*file)[5] = (unsigned char)(file_size >> 24);
	(*file)[10] = (unsigned char)(14 + 40);
}

static void	ft_create_bitmap_info_header(t_game *game, unsigned char **file)
{
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

int		ft_header_create(t_game *game, unsigned char **file, int fd)
{
	unsigned int	size;

	size = game->screen.width * game->screen.height * 4;
	(*file) = ft_calloc(size + 54, 1);
	if (!(*file))
	{
		close(fd);
		return (ft_trash_game(game, allocation_fail, -1, "Fuction ft_header_create | line 17\n"));
	}
	ft_create_bitmap_file_header(size, file);
	ft_create_bitmap_info_header(game, file);
	return (0);
}

int		ft_image_save(t_game *game)
{
	int				fd;
	unsigned char	*file;
	int				y;
	int				x;
	int				j;
	int				id;

	fd = open("./img.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (fd < 0)
		return (ft_trash_game(game, open_file_fail, -1, "function ft_image_save | line 33\n"));
	ft_header_create(game, &file, fd);
	y = game->screen.height;
	j = 0;
	id = 0;
	while (--y >= 0)
	{
		x = -1;
		while (++x < game->screen.size)
		{
			file[54 + id] = (unsigned char)(game->screen.color[y * game->screen.size + x]);
			file[54 + id + 1] = (unsigned char)(game->screen.color[y * game->screen.size + x] >> 8);
			file[54 + id + 2] = (unsigned char)(game->screen.color[y * game->screen.size + x] >> 16);
			file[54 + id + 3] = (unsigned char)(game->screen.color[y * game->screen.size + x] >> 24);
			id += 4;
		}
		j++;
	}
	write(fd, file, game->screen.width * game->screen.height * 4 + 54);
	close(fd);
	return (ft_trash_game(game, succes, -1, "Image create !\n"));
}

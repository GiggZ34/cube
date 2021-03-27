/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:00:33 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:35:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_header_create(t_game *game, char **header, int fd)
{
	*header = ft_calloc(54, 1);
	if (!(*header))
	{
		close(fd);
		return (ft_trash_game(game, allocation_fail, -1, "Fuction ft_header_create | line 17\n"));
	}
//	header->flag = "BM";
//	header->file_size = (char*)(&game->screen.size);
	return (0);
}

int		ft_image_save(t_game *game)
{
	int			fd;
	char		*header;

	fd = open("./img.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (fd < 0)
		return (ft_trash_game(game, open_file_fail, -1, "function ft_image_save | line 33\n"));
	ft_header_create(game, &header, fd);
//	write(1, header, ft_strlen(header));
	long long test = 522023;
	char *bin;
	ft_decbin(&bin, test);
	printf("%s | %lld\n", bin, test);
	free(bin);
	test = test << 8;
	ft_decbin(&bin, test);
	printf("%s | %lld\n", bin, test);
	test = test >> 6;
	ft_decbin(&bin, test);
	printf("%s | %lld\n", bin, test);
	free(bin);
//	printf("%d\n", test >> 8);
	close(fd);
	return (ft_trash_game(game, succes, -1, "Image create !\n"));
}

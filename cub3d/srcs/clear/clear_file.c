/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:01:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/01 12:18:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_del_texture(t_texture *texture)
{
	int			i;

	i = -1;
	while (++i < texture->height)
	{
		free(texture->color[i]);
		texture->color[i] = NULL;
	}
	texture->endian = 0;
	texture->bits_per_pixel = 0;
	texture->height = 0;
	texture->type = NULL;
	texture->size_line = 0;
	texture->width = 0;
}

int			ft_clear_file(t_file *file, int fd, int code_error)
{
	char	*s;

	s = 0;
	while (get_next_line(fd, &s) == 1)
		if (s)
			free(s);
	if (s)
		free(s);
	if (file)
	{
		file->error_code = code_error;
		if (file->texture_ea)
			ft_del_texture(file->texture_ea);
		if (file->texture_we)
			ft_del_texture(file->texture_we);
		if (file->texture_no)
			ft_del_texture(file->texture_no);
		if (file->texture_so)
			ft_del_texture(file->texture_so);
		if (file->texture_s)
			ft_del_texture(file->texture_s);
		if (file->map)
			ft_free_array(file->map);
	}
	return (code_error);
}

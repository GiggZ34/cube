/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:08:29 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/07 18:22:45 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_search_extension(char *dir_img)
{
	char	*ext;
	int		value;

	value = -1;
	if (!(ext = ft_substr(dir_img, -3, 3)))
		return (value);
	if (ft_strncmp(ext, "png", 3) == 0)
		value = 0;
	else if (ft_strncmp(ext, "xpm", 3) == 0)
		value = 1;
	free(ext);
	return (value);
}

static int	ft_image_to_struct(t_file *file, void *img, int *dim, char *type)
{
	t_texture	*texture;
	int			*texture_bits;

	if (!(texture = ft_calloc(sizeof(t_texture), 1)))
		return (3);
	texture->type = type;
	texture->width = dim[0];
	texture->height = dim[1];
	if (!(texture_bits = (int*)mlx_get_data_addr(img,
	&(texture->bits_per_pixel), &(texture->size_line), &(texture->endian))))
		return (3);
	texture->size_line /= sizeof(*texture_bits);
	if (!(texture->color = ft_nsplit(texture_bits, texture->size_line * dim[1], texture->size_line)))
		return (3);
	if (!ft_strncmp(type, "NO", 2))
		file->texture_no = texture;
	else if (!ft_strncmp(type, "SO", 2))
		file->texture_so = texture;
	else if (!ft_strncmp(type, "EA", 2))
		file->texture_ea = texture;
	else if (!ft_strncmp(type, "WE", 2))
		file->texture_we = texture;
	else if (!ft_strncmp(type, "S", 2))
		file->texture_s = texture;
	return (0);
}

int			ft_img_generate(void *mlx, t_file *file, char *dir, char *type)
{
	void	*img;
	int		dim[2];
	int		ext;

	if ((ext = ft_search_extension(dir)) == 1)
	{
		if (!(img = mlx_xpm_file_to_image(mlx, dir, &dim[0], &dim[1])))
			return (10);
	}
//	else if (ext == 0)
//	{
//		if (!(img = mlx_png_file_to_image(mlx, dir, &dim[0], &dim[1])))
//			return (10);
//	}
	else
		return (9);
	if (ft_image_to_struct(file, img, dim, type) == -1)
		return (3);
	free(img);
	return (0);
}

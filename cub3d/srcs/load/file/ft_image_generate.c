/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:08:29 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/03 14:17:36 by grivalan         ###   ########lyon.fr   */
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

static int	ft_image_to_struct(t_game *game, void *img, int *dim, char *type)
{
	t_texture	*texture;

	if (!(texture = ft_calloc(sizeof(t_texture), 1)))
		return (ft_trash_game(game, allocation_fail, -1, "Function ft_image_to_struct | line 35\n"));
	texture->ptr = img;
	texture->type = type;
	texture->width = dim[0];
	texture->height = dim[1];
	if (!(texture->color = (int*)mlx_get_data_addr(img,
	&(texture->bits_per_pixel), &(texture->size_line), &(texture->endian))))
		return (ft_trash_game(game, color_generation_fail, -1, "Function ft_image_to_struct | line 41\n"));
	texture->size_line /= 4;
	if (!ft_strncmp(type, "NO", 2))
		game->file.texture_no = texture;
	else if (!ft_strncmp(type, "SO", 2))
		game->file.texture_so = texture;
	else if (!ft_strncmp(type, "EA", 2))
		game->file.texture_ea = texture;
	else if (!ft_strncmp(type, "WE", 2))
		game->file.texture_we = texture;
	else if (!ft_strncmp(type, "S", 2))
		game->file.texture_s = texture;
	return (0);
}

int			ft_img_generate(t_game *game, char *dir, char *type)
{
	void	*img;
	int		dim[2];
	int		ext;

	if ((ext = ft_search_extension(dir)) == 1)
	{
		if (!(img = mlx_xpm_file_to_image(game->mlx, dir, &dim[0], &dim[1])))
			return (ft_trash_game(game, crash_mlx_function, -1, "Function ft_img_generate | line 66\n"));
	}
	else if (ext == 0)
	{
		if (!(img = mlx_png_file_to_image(game->mlx, dir, &dim[0], &dim[1])))
			return (ft_trash_game(game, crash_mlx_function, -1, "PNG"));
	}
	else
		return (ft_trash_game(game, image_not_exist, -1, "Extension invalid\n"));
	ft_image_to_struct(game, img, dim, type);
	return (0);
}

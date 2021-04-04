/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:08:29 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 19:36:32 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	texture_obj_to_back(t_game *game, t_texture *texture)
{
	t_texture	*obj;

	if (!game->file.texture_obj)
		game->file.texture_obj = texture;
	else
	{
		obj = game->file.texture_obj;
		while (obj->next)
			obj = obj->next;
		obj->next = texture;
	}
}

static int	ft_search_extension(char *dir_img)
{
	char	*ext;
	int		value;

	value = -1;
	ext = ft_substr(dir_img, -3, 3);
	if (!ext)
		return (value);
	if (ft_strncmp(ext, "png", 3) == 0)
		value = 0;
	else if (ft_strncmp(ext, "xpm", 3) == 0)
		value = 1;
	free(ext);
	return (value);
}

static void	save_texture(t_game *game, t_texture *texture, char *type)
{
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
	else if (!ft_strncmp(type, "LI", 2))
		game->file.texture_light = texture;
	else
		texture_obj_to_back(game, texture);
}

static int	ft_image_to_struct(t_game *game, void *img, int *dim, char *type)
{
	t_texture	*texture;

	texture = ft_calloc(sizeof(t_texture), 1);
	if (!texture)
		return (ft_trash_game(game,
				allocation_fail, -1, "In ft_image_to_struct"));
	texture->ptr = img;
	texture->type = type;
	texture->width = dim[0];
	texture->height = dim[1];
	texture->next = NULL;
	texture->color = (int *)mlx_get_data_addr(img, &(texture->bits_per_pixel),
			&(texture->size_line), &(texture->endian));
	if (!texture->color)
		return (ft_trash_game(game,
				color_generation_fail, -1, "In image_to_struct"));
	texture->size_line /= 4;
	save_texture(game, texture, type);
	return (0);
}

int	ft_img_generate(t_game *game, char *dir, char *type)
{
	void	*img;
	int		dim[2];
	int		ext;

	img = NULL;
	if (!type)
		ft_trash_game(game,
			allocation_fail, game->file.fd, "In ft_img_generate");
	ext = ft_search_extension(dir);
	if (ext == 1)
	{
		img = mlx_xpm_file_to_image(game->mlx, dir, &dim[0], &dim[1]);
		if (!img)
			ft_trash_game(game,
				crash_mlx_ft, game->file.fd, "In ft_img_generate");
	}
	else if (ext == 0)
	{
		img = mlx_png_file_to_image(game->mlx, dir, &dim[0], &dim[1]);
		if (!img)
			ft_trash_game(game,
				crash_mlx_ft, game->file.fd, "In ft_img_generate");
	}
	else
		ft_trash_game(game,
			image_not_exist, game->file.fd, "Extension invalid\n");
	ft_image_to_struct(game, img, dim, type);
	return (0);
}

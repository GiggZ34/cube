/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:21:03 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/16 16:32:38 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_screen_unvisible(t_game *game, t_screen s)
{
	int i;

	i = -1;
	while (++i < game->screen.height * game->screen.size)
		s.color[i] = UNVISIBLE_COLOR;
}

static void	ft_generate_texture(t_game *game, t_screen s, int state, int num_img)
{
	double	h_color;
	double	w_color;
	int		w;
	int		h;

	w = game->player->guns.position.x;
	h = game->player->guns.position.y;
	h_color = game->player->guns.height * state;
	w_color = game->player->guns.width * num_img;
	while (h * s.size + w < s.height * s.size)
	{
		s.color[h * s.size + w] = game->player->guns.obj_texture.color[(int)h_color * game->player->guns.obj_texture.size_line + (int)w_color];
		w_color += game->player->guns.ratio;
		w++;
		if ((int)w_color >= game->player->guns.width * (num_img + 1))
		{
			w_color = game->player->guns.width * num_img;
			h_color += game->player->guns.ratio;
			w = game->player->guns.position.x;
			h++;
		}
		printf("%d | %d\n", (int)h_color * game->player->guns.obj_texture.size_line + (int)w_color, game->player->guns.width * game->player->guns.height);
	}
}

int			ft_init_screen(t_game *game, t_screen *img, int num_img, int state)
{
	int	i;

	i = -1;
	while (++i < num_img)
	{
		if (!(img[i].ptr = mlx_new_image(game->mlx,
									game->screen.width, game->screen.height)))
			return (game->file->error_code = 3);
		img[i].height = game->screen.height;
		if (!(img[i].color = (int*)mlx_get_data_addr(img[i].ptr,
				&img[i].bit, &img[i].size, &img[i].endian)))
			return (game->file->error_code = 3);
		img[i].size /= 4;
		ft_screen_unvisible(game, img[i]);
		ft_generate_texture(game, img[i], state, i);
	}
	return (0);
}

int			ft_screen(t_game *game)
{
	if (!(game->screen.ptr = mlx_new_image(game->mlx,
									game->screen.width, game->screen.height)))
		return (game->file->error_code = 3);
	if (!(game->screen.color = (int*)mlx_get_data_addr(game->screen.ptr,
				&game->screen.bit, &game->screen.size, &game->screen.endian)))
		return (game->file->error_code = 3);
	game->screen.w_vec = (1 / FOV) / game->screen.size;
	game->screen.size /= 4;
	game->screen.scale = 1;
	return (0);
}


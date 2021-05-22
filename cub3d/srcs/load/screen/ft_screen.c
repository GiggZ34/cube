/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:21:03 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 16:06:30 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_screen_unvisible(t_game *game, t_screen s)
{
	int	i;

	i = -1;
	while (++i < game->screen.height * game->screen.size)
		s.color[i] = INVISIBLE_COLOR;
}

static void	ft_generate_texture(t_game *g, t_screen s, int state, int num_img)
{
	double	h_color;
	double	w_color;
	int		w;
	int		h;

	w = g->player.guns.position.x;
	h = g->player.guns.position.y;
	h_color = g->player.guns.height * state;
	w_color = g->player.guns.width * num_img;
	while (h * s.size + w < s.height * s.size)
	{
		s.color[h * s.size + w] = g->player.guns.obj_texture.color[
			(int)h_color * g->player.guns.obj_texture.size_line
			+ (int)w_color];
		w_color += g->player.guns.ratio_size;
		w++;
		if ((int)w_color >= g->player.guns.width * (num_img + 1))
		{
			w_color = g->player.guns.width * num_img;
			h_color += g->player.guns.ratio_size;
			w = g->player.guns.position.x;
			h++;
		}
	}
}

int	ft_init_screen(t_game *game, t_screen *img, int num_img, int state)
{
	int	i;

	i = -1;
	while (++i < num_img)
	{
		img[i].ptr = mlx_new_image(game->mlx,
				game->screen.width, game->screen.height);
		if (!img[i].ptr)
			return (ft_trash_game(game, load_texture_fail, -1, "\n"));
		img[i].height = game->screen.height;
		img[i].color = (int *)mlx_get_data_addr(img[i].ptr,
				&img[i].bit, &img[i].size, &img[i].endian);
		if (!(img[i].color))
			return (ft_trash_game(game, color_generation_fail, -1, "\n"));
		img[i].size /= 4;
		ft_screen_unvisible(game, img[i]);
		ft_generate_texture(game, img[i], state, i);
	}
	return (0);
}

int	ft_screen(t_game *game)
{
	game->screen.ptr = mlx_new_image(game->mlx,
			game->screen.width, game->screen.height);
	if (!game->screen.ptr)
		return (ft_trash_game(game, load_texture_fail, -1, "\n"));
	game->screen.color = (int *)mlx_get_data_addr(game->screen.ptr,
			&game->screen.bit, &game->screen.size, &game->screen.endian);
	if (!game->screen.color)
		return (ft_trash_game(game, color_generation_fail, -1, "\n"));
	game->screen.size /= 4;
	game->screen.w_vec = 2 * tan(ft_deg_to_rad(FOV) / 2) / game->screen.width;
	game->screen.h_vec = 2 * tan(ft_deg_to_rad(FOV * game->screen.height
				/ game->screen.width) / 2) / game->screen.height;
	game->screen.scale = 1;
	return (0);
}

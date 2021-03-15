/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:21:03 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/15 14:17:14 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_screen_unvisible(t_screen s)
{
	int i;

	i = -1;
	while (++i < s.height * s.size)
		s.color[i] = UNVISIBLE_COLOR;
}

static void	ft_generate_texture(t_game *game, t_screen s, int state, int nb_img)
{
	int i;

	i = game->player->guns.position.y * s.size + game->player->guns.position.x;
	while (i < s.size * s.height)
	{

	}

}

int			ft_init_screen(t_game *game, t_screen *img, int nb_img, int state)
{
	int	i;

	i = -1;
	while (++i < nb_img)
	{
		if (!(img[i].ptr = mlx_new_image(game->mlx,
									game->screen.width, game->screen.height)))
			return (game->file->error_code = 3);
		if (!(img[i].color = (int*)mlx_get_data_addr(img[i].ptr,
				&img[i].bit, &img[i].size, &img[i].endian)))
			return (game->file->error_code = 3);
		img[i].size /= 4;
		ft_screen_unvisible(img[i]);
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

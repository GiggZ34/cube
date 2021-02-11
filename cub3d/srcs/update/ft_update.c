/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/11 14:33:21 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_keypress(int keycode, t_game *game)
{
	if (keycode == 53)
		return (mlx_destroy_window(game->mlx, game->window));
	if (keycode == 124)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'z');
	else if (keycode == 123)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'z');
	if (keycode == 126)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'x');
	else if (keycode == 125)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'x');
	if (keycode == 13)
		ft_translation_vector(game, -0.5, 0);
	else if (keycode == 1)
		ft_translation_vector(game, 0.5, 0);
	if (keycode == 2)
		ft_translation_vector(game, -0.5, -M_PI / 2);
	else if (keycode == 0)
		ft_translation_vector(game, -0.5, M_PI / 2);
	return (0);
}

int		ft_update(t_game *game)
{
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
	mlx_loop_hook(game->mlx, &ft_draw, game);
	mlx_loop(game->mlx);
	return (0);
}

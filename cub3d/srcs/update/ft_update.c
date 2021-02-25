/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/15 12:07:34 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_keypress(int keycode, t_game *game)
{
	if (keycode == 53)
		return (mlx_destroy_window(game->mlx, game->window));
// rotate view to left : mac keycode = 124 | linux keycode = 65363
	if (keycode == 65363)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'z');
// rotate view to right : mac keycode = 123 | linux keycode = 65361
	else if (keycode == 65361)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'z');
// rotate view to down : mac keycode = 126 | linux keycode = 65364
	if (keycode == 65364)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'x');
// rotate view to up : mac keycode = 125 | linux keycode = 65362
	else if (keycode == 65362)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'x');
// move to forward : mac keycode = 13 | linux keycode = 119
	if (keycode == 119)
		ft_translation_vector(game, -0.5, 0);
// move to backward : mac keycode = 1 | linux keycode = 115
	else if (keycode == 115)
		ft_translation_vector(game, 0.5, 0);
// move to left : mac keycode = 2 | linux keycode = 113
	if (keycode == 97)
		ft_translation_vector(game, -0.5, M_PI / 2);
// move to right : mac keycode = 0 | linux keycode = 100
	else if (keycode == 100)
		ft_translation_vector(game, -0.5, -M_PI / 2);
//	dprintf(1, "v_p = %f | %f\n", game->player->view.view.x, game->player->view.view.y);
	ft_draw(game);
	return (0);
}

int		ft_update(t_game *game)
{
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
//	mlx_loop_hook(game->mlx, &ft_draw, game);
	mlx_loop(game->mlx);
	return (0);
}

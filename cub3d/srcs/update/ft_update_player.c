/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:44:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/13 16:02:03 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_define_angle_move(t_player *player)
{
	if (player->control.w)
		player->dir_walk = -M_PI / 2;
	else if (player->control.s)
		player->dir_walk = M_PI / 2;
	if (player->control.a)
		player->dir_trans = M_PI;
	else if (player->control.d)
		player->dir_trans = 0;
}

static void	ft_define_angle_player(t_game *game)
{
	if (game->player->angle_z < 0)
		game->player->angle_z += 2 * M_PI;
	else if (game->player->angle_z >= 2 * M_PI)
		game->player->angle_z -= 2 * M_PI;
	if (game->player->angle_x < -M_PI / 3)
		game->player->angle_x = -M_PI / 3;
	else if (game->player->angle_x >= M_PI / 2)
		game->player->angle_x = M_PI / 2;
}

int		ft_update_player(t_game *game, t_player *player)
{
	int	*x;
	int *y;

	x = &(game->player->control.mouse_x_tmp);
	y = &(game->player->control.mouse_y_tmp);
	mlx_mouse_get_pos(game->window, x, y);
//	mlx_mouse_get_pos(game->mlx, game->window, x, y);
	mlx_mouse_move(game->window, game->player->control.mouse_x,
												game->player->control.mouse_y);
//	mlx_mouse_move(game->mlx, game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	mlx_mouse_get_pos(game->window, &(game->player->control.mouse_x),
											&(game->player->control.mouse_y));
//	mlx_mouse_get_pos(game->mlx, game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
	mlx_mouse_move(game->window, game->player->control.mouse_x,
											game->player->control.mouse_y);
//	mlx_mouse_move(game->mlx, game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	ft_define_angle_move(player);
	ft_rotate_player(game, player, *x - game->player->control.mouse_x,
										*y - game->player->control.mouse_y);
	ft_move_player(game, player);
	ft_define_angle_player(game);
	return (0);
}

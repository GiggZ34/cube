/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:44:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 23:58:44 by grivalan         ###   ########lyon.fr   */
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

static void ft_rotate_player(t_game *game, t_player *player, double x, double y)
{
    if (player->control.right || ft_abs(player->control.mouse_x) - ft_abs(x) > MOUSE_SENS)
	{
		game->player->angle_z += -ROTATE_SPEED * game->dt.dt;
		ft_rotate_vectors_collides(player, -ROTATE_SPEED * game->dt.dt);
	}
	else if (player->control.left || ft_abs(x) - ft_abs(game->player->control.mouse_x) > MOUSE_SENS)
	{
		game->player->angle_z += ROTATE_SPEED * game->dt.dt;
		ft_rotate_vectors_collides(player, ROTATE_SPEED * game->dt.dt);
	}
    if (player->control.up || y - player->control.mouse_y > MOUSE_SENS)
		game->player->angle_x += -ROTATE_SPEED * game->dt.dt;
	else if (player->control.down || player->control.mouse_y - y > MOUSE_SENS)
		game->player->angle_x += ROTATE_SPEED * game->dt.dt;
}

static void ft_define_move_player(t_game *game, t_player *player)
{
	if (player->control.a || player->control.d)
		ft_player_move(game, SPEED_MAX, &player->walk_speed, player->dir_trans);
	else
		ft_player_move(game, -SPEED_MAX, &player->walk_speed, player->dir_trans);
	if (player->control.w || player->control.s)
		ft_player_move(game, SPEED_MAX, &player->trans_speed, player->dir_walk);
	else
		ft_player_move(game, -SPEED_MAX, &player->trans_speed, player->dir_walk);
}

static void ft_define_angle_player(t_game *game)
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
	mlx_mouse_move(game->window, game->player->control.mouse_x, game->player->control.mouse_y);
//	mlx_mouse_move(game->mlx, game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	mlx_mouse_get_pos(game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
//	mlx_mouse_get_pos(game->mlx, game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
	mlx_mouse_move(game->window, game->player->control.mouse_x, game->player->control.mouse_y);
//	mlx_mouse_move(game->mlx, game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	ft_define_angle_move(player);
    ft_rotate_player(game, player, *x, *y);
    ft_define_move_player(game, player);
    ft_define_angle_player(game);
	return (0);
}

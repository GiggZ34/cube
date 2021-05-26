/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 17:06:16 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	keypress_next(int keycode, t_game *game)
{
	if (keycode == SHOOT && !game->player.control.reload)
		game->player.control.shoot = 1;
	if (keycode == SPACE && !game->player.control.squat
		&& game->player.position.z == game->player.pos_z_min)
		game->player.vz = 3;
	if (keycode == L && !game->debug && game->light)
		game->debug = 1;
	else if (keycode == L && game->debug)
		game->debug = 0;
	if (keycode == P)
		game->save_picture = 1;
	return (0);
}

static int	ft_keypress(int keycode, t_game *game)
{
	if (keycode == DESTROY)
		return (ft_trash_game(game, succes, -1, ""));
	if (keycode == RIGHT)
		game->player.control.right = 1;
	else if (keycode == LEFT)
		game->player.control.left = 1;
	if (keycode == UP)
		game->player.control.up = 1;
	else if (keycode == DOWN)
		game->player.control.down = 1;
	if (keycode == A)
		game->player.control.a = 1;
	else if (keycode == D)
		game->player.control.d = 1;
	if (keycode == W)
		game->player.control.w = 1;
	else if (keycode == S)
		game->player.control.s = 1;
	else if (keycode == ALT)
		game->player.control.squat = 1;
	if (keycode == SHIFT)
		game->player.control.run = 1;
	return (keypress_next(keycode, game));
}

static int	ft_keyrelease(int keycode, t_game *game)
{
	if (keycode == RIGHT)
		game->player.control.right = 0;
	else if (keycode == LEFT)
		game->player.control.left = 0;
	if (keycode == UP)
		game->player.control.up = 0;
	else if (keycode == DOWN)
		game->player.control.down = 0;
	if (keycode == A)
		game->player.control.a = 0;
	else if (keycode == D)
		game->player.control.d = 0;
	if (keycode == W)
		game->player.control.w = 0;
	else if (keycode == S)
		game->player.control.s = 0;
	if (keycode == SHIFT)
		game->player.control.run = 0;
	else if (keycode == ALT)
		game->player.control.squat = 0;
	return (0);
}

static int	ft_update(t_game *game)
{
	if (!game->exit)
		playmusic(game);
	ft_delta_time_generate(game);
	ft_update_player(game, &game->player);
	ft_update_sprites(game->lst_sprites, &game->player);
	ft_update_planes(game);
	if (game->window)
		mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->window);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->screen.ptr);
	ft_draw_multi_threads(game, game->player.arm);
	return (0);
}

int	ft_game_loop(t_game *game)
{
	if (game->window)
	{
		mlx_mouse_hook(game->window, ft_mouse_press, game);
		mlx_hook(game->window, 6, 1L << 6, &mouse_move, game);
		mlx_hook(game->window, 17, 1L << 17, &ft_trash_game, game);
		mlx_hook(game->window, 2, 1L << 0, ft_keypress, game);
		mlx_hook(game->window, 3, 1L << 1, ft_keyrelease, game);
	}
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/17 14:33:42 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_delete_textures(t_game *game)
{
	if (game->file->texture_ea)
	{
		if (mlx_destroy_image(game->mlx, game->file->texture_ea->ptr))
			printf("Texture east destruction failed\n");
		free(game->file->texture_ea);
	}
	if (game->file->texture_no)
	{
		if (mlx_destroy_image(game->mlx, game->file->texture_no->ptr))
			printf("Texture north destruction failed\n");
		free(game->file->texture_no);
	}
	if (game->file->texture_s)
	{
		if (mlx_destroy_image(game->mlx, game->file->texture_s->ptr))
			printf("Texture sprite destruction failed\n");
		free(game->file->texture_s);
	}
	if (game->file->texture_so)
	{
		if (mlx_destroy_image(game->mlx, game->file->texture_so->ptr))
			printf("Texture south destruction failed\n");
		free(game->file->texture_so);
	}
	if (game->file->texture_we)
	{
		if (mlx_destroy_image(game->mlx, game->file->texture_we->ptr))
			printf("Texture west destruction failed\n");
		free(game->file->texture_we);
	}
}

int		ft_trash_game(t_game *game)
{
	ft_clear_file(game->file, 3, 0);
	ft_delete_textures(game);
	if (mlx_destroy_window(game->mlx, game->window))
			printf("Windows destruction failed\n");
	exit(0);
}

int		ft_keypress(int keycode, t_game *game)
{
	if (keycode == DESTROY)
		return (ft_trash_game(game));
	if (keycode == RIGHT)
		game->player->control.right = 1;
	else if (keycode == LEFT)
		game->player->control.left = 1;
	if (keycode == UP)
		game->player->control.up = 1;
	else if (keycode == DOWN)
		game->player->control.down = 1;
	if (keycode == A)
		game->player->control.a = 1;
	else if (keycode == D)
		game->player->control.d = 1;
	if (keycode == W)
		game->player->control.w = 1;
	else if (keycode == S)
		game->player->control.s = 1;
	else if (keycode == ALT)
		game->player->control.squat = 1;
	if (keycode == SHIFT)
		game->player->control.run = 1;
	if (keycode == SHOOT && !game->player->control.reload)
		game->player->control.shoot = 1;
	return (0);
}

int		ft_keyrelease(int keycode, t_game *game)
{
	if (keycode == RIGHT)
		game->player->control.right = 0;
	else if (keycode == LEFT)
		game->player->control.left = 0;
	if (keycode == UP)
		game->player->control.up = 0;
	else if (keycode == DOWN)
		game->player->control.down = 0;
	if (keycode == A)
		game->player->control.a = 0;
	else if (keycode == D)
		game->player->control.d = 0;
	if (keycode == W)
		game->player->control.w = 0;
	else if (keycode == S)
		game->player->control.s = 0;
	if (keycode == SHIFT)
		game->player->control.run = 0;
	else if (keycode == ALT)
		game->player->control.squat = 0;
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1 && !game->player->control.reload)
		game->player->control.shoot = 1;
	else if (button == 2)
		game->player->control.reload = 1;
	x = 0;
	y = 0;
	return (0);
}

int		ft_update(t_game *game)
{
	ft_delta_time_generate(game);
	ft_update_player(game, game->player);
	ft_update_sprites(game->lst_sprites, game->player);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->window);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->screen.ptr);
	ft_draw_multi_threads(game, game->player->arm);
	return (0);
}

int		ft_game_loop(t_game *game)
{
	mlx_mouse_hide();
//	mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_get_pos(game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
//	mlx_mouse_get_pos(game->mlx, game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
	mlx_mouse_hook(game->window, ft_mouse_press, game);
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
	mlx_hook(game->window, 3, 1L<<1, ft_keyrelease, game);
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

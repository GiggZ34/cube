/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/23 14:48:49 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_delete_textures(t_game *game)
{
	if (game->file.texture_ea)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_ea->ptr))
			printf("Error\nTexture east destruction failed\n");
		free(game->file.texture_ea);
	}
	if (game->file.texture_no)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_no->ptr))
			printf("Error\nTexture north destruction failed\n");
		free(game->file.texture_no);
	}
	if (game->file.texture_s)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_s->ptr))
			printf("Error\nTexture sprite destruction failed\n");
		free(game->file.texture_s);
	}
	if (game->file.texture_so)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_so->ptr))
			printf("Error\nTexture south destruction failed\n");
		free(game->file.texture_so);
	}
	if (game->file.texture_we)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_we->ptr))
			printf("Error\nTexture west destruction failed\n");
		free(game->file.texture_we);
	}
	if (game->sky_ground.ground_texture.ptr)
	{
		if (mlx_destroy_image(game->mlx, game->sky_ground.ground_texture.ptr))
			printf("Error\nTexture ground destruction failed\n");
	}
	if (game->sky_ground.sky_texture.ptr)
	{
		if (mlx_destroy_image(game->mlx, game->sky_ground.sky_texture.ptr))
			printf("Error\nTexture sky destruction failed\n");
	}
}

void	delete(void *content)
{
	free(content);
	content = NULL;
}

int		ft_free_hud(t_game *g, t_player *p)
{
	int	i;
	int	j;
	int	nb_frame;

	if (p->gun[0])
	{
		i = -1;
		while (++i < NB_ANIM_GUNS)
		{
			nb_frame = ft_define_nb_anim(i);
			j = -1;
			while (++j < nb_frame)
				mlx_destroy_image(g->mlx, p->gun[i][j].ptr);
		}
	}
	return (0);
}

int		ft_trash_game(t_game *game, t_error_code code, int fd)
{
	ft_clear_file(&game->file, fd, code);
	ft_delete_textures(game);
	ft_free_hud(game, &game->player);
	ft_lstclear(&game->lst_sprites, &delete, 1);
	ft_lstclear(&game->lst_planes_bottom, &delete, 1);
	ft_lstclear(&game->lst_planes_top, &delete, 1);
	ft_lstclear(&game->lst_planes_left, &delete, 1);
	ft_lstclear(&game->lst_planes_right, &delete, 1);
	ft_lstclear(&game->player.view.sprites_in_fov, &delete, 0);
	if (game->tab_planes.bottom)
		free(game->tab_planes.bottom);
	if (game->tab_planes.top)
		free(game->tab_planes.top);
	if (game->tab_planes.left)
		free(game->tab_planes.left);
	if (game->tab_planes.right)
		free(game->tab_planes.right);
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx, game->screen.ptr);
	if (game->dt.dt_str)
		free(game->dt.dt_str);
	if (game->player.guns.obj_texture.ptr)
		mlx_destroy_image(game->mlx, game->player.guns.obj_texture.ptr);
	if (game->player.view.tab_vectors)
		free(game->player.view.tab_vectors);
	if (game->window)
	{
		mlx_clear_window(game->mlx, game->window);
		if (mlx_destroy_window(game->mlx, game->window))
			printf("Windows destruction failed\n");
	}
//	while(1);
	exit(code);
}

int		ft_keypress(int keycode, t_game *game)
{
	if (keycode == DESTROY)
		return (ft_trash_game(game, succes, -1));
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
	if (keycode == SHOOT && !game->player.control.reload)
		game->player.control.shoot = 1;
	return (0);
}

int		ft_keyrelease(int keycode, t_game *game)
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

int		ft_mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1 && !game->player.control.reload)
		game->player.control.shoot = 1;
	else if (button == 2)
		game->player.control.reload = 1;
	if (x == 0 && y == 0)
		return (0);
	return (0);
}

int		ft_update(t_game *game)
{
	ft_delta_time_generate(game);
	ft_update_player(game, &game->player);
	ft_update_sprites(/*game, */game->lst_sprites, &game->player);
//	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->window);
//	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->screen.ptr);
	ft_draw_multi_threads(game, game->player.arm);
	return (0);
}

int		ft_game_loop(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->window);
//	mlx_mouse_get_pos(game->window, &(game->player.control.mouse_x), &(game->player.control.mouse_y));
	mlx_mouse_get_pos(game->mlx, game->window, &(game->player.control.mouse_x), &(game->player.control.mouse_y));
	mlx_mouse_hook(game->window, ft_mouse_press, game);
	mlx_hook(game->window, 17, 1L<<17, &ft_trash_game, game);
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
	mlx_hook(game->window, 3, 1L<<1, ft_keyrelease, game);
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

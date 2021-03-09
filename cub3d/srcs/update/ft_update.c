/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 16:08:00 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_collide_to_sprite(t_plane plane, t_collide collide, t_dot pos)
{
	if (ft_size_vec_plane(&plane, collide.top, pos) < DIST_COLLIDE)
	{
		collide.top_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.bottom, pos) < DIST_COLLIDE)
	{
		collide.bottom_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.left, pos) < DIST_COLLIDE)
	{
		collide.left_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.right, pos) < DIST_COLLIDE)
	{
		collide.right_bool = 1;
		return ;
	}
}

void	ft_search_sprites(t_sprite *sprite, t_list **begin, t_player *player)
{
	t_vector	vec;
	t_list		*lst;
	int			dist;

	vec = ft_create_vector(sprite->position, player->position);
	dist = pow(player->position.x - sprite->position.x, 2) +
								pow(player->position.y - sprite->position.y, 2);
	ft_check_collide_to_sprite(sprite->plane, player->collide, player->position);
	if (ft_dot_product(player->collide.top, vec) < FOV_COS && dist <= FOV_DIST)
	{
		lst = ft_lstnew(sprite);
		ft_lstadd_back(begin, lst);
	}
}

void	ft_play(void *s)
{
	if (s)
		return ;
	return ;
}

int		ft_update_sprites(t_list *lst_sprites, t_player *player)
{
	t_sprite	*sprite;

	ft_lstclear(&(player->view.sprites_in_fov), &ft_play, 0);
	while (lst_sprites)
	{
		sprite = lst_sprites->content;
		ft_edit_sprite_plane(sprite, player->view.view);
		sprite->position.y -= 0.0;
		ft_search_sprites(sprite, &(player->view.sprites_in_fov), player);
		lst_sprites = lst_sprites->next;
	}
	return (0);
}

int		ft_trash_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->file->texture_ea);
	mlx_destroy_image(game->mlx, game->file->texture_no);
	mlx_destroy_image(game->mlx, game->file->texture_s);
	mlx_destroy_image(game->mlx, game->file->texture_so);
	mlx_destroy_image(game->mlx, game->file->texture_we);
	mlx_destroy_window(game->mlx, game->window);
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
	if (keycode == SHIFT)
		game->player->control.run = 1;
	else if (keycode == ALT)
		game->player->position.z += 0.25;
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
		game->player->position.z -= 0.25;
	return (0);
}

int		ft_update_player(t_game *game, t_player *player)
{
	int	*x;
	int *y;

	x = &(game->player->control.mouse_x_tmp);
	y = &(game->player->control.mouse_y_tmp);
	mlx_mouse_get_pos(game->window, x, y);
	mlx_mouse_move(game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	mlx_mouse_get_pos(game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
	mlx_mouse_move(game->window, game->player->control.mouse_x, game->player->control.mouse_y);
	if (player->control.right || ft_abs(game->player->control.mouse_x) - ft_abs(*x) > MOUSE_SENS)
	{
		game->player->angle_z += -ROTATE_SPEED * game->dt.dt;
		ft_rotate_vectors_collides(game->player, -ROTATE_SPEED * game->dt.dt);
	}
	else if (player->control.left || ft_abs(*x) - ft_abs(game->player->control.mouse_x) > MOUSE_SENS)
	{
		game->player->angle_z += ROTATE_SPEED * game->dt.dt;
		ft_rotate_vectors_collides(game->player, ROTATE_SPEED * game->dt.dt);
	}
	if (player->control.up || *y - game->player->control.mouse_y > MOUSE_SENS)
		game->player->angle_x += -ROTATE_SPEED * game->dt.dt;
	else if (player->control.down || game->player->control.mouse_y - *y > MOUSE_SENS)
		game->player->angle_x += ROTATE_SPEED * game->dt.dt;
	if (player->control.a)
		ft_translation_vector(game, -SPEED_MAX, 0);
	else if (player->control.d)
		ft_translation_vector(game, SPEED_MAX, 0);
	if (player->control.w)
		ft_translation_vector(game, -SPEED_MAX, M_PI / 2);
	else if (player->control.s)
		ft_translation_vector(game, -SPEED_MAX, -M_PI / 2);
	if (game->player->angle_z < 0)
		game->player->angle_z += 2 * M_PI;
	else if (game->player->angle_z >= 2 * M_PI)
		game->player->angle_z -= 2 * M_PI;
	if (game->player->angle_x < -M_PI / 3)
		game->player->angle_x = -M_PI / 3;
	else if (game->player->angle_x >= M_PI / 2)
		game->player->angle_x = M_PI / 2;
	return (0);
}

int		ft_update(t_game *game)
{
	ft_delta_time_generate(game);
	ft_update_player(game, game->player);
	ft_update_sprites(game->lst_sprites, game->player);
	ft_draw(game);
	return (0);
}

int		ft_game_loop(t_game *game)
{
	mlx_mouse_get_pos(game->window, &(game->player->control.mouse_x), &(game->player->control.mouse_y));
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
	mlx_hook(game->window, 3, 1L<<1, ft_keyrelease, game);
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

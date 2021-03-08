/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/08 19:11:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_collide(t_plane plane, t_collide collide, t_dot pos)
{
	if (ft_size_vec_plane(&plane, collide.top, pos) < 2)
	{
		collide.top_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.bottom, pos) < 2)
	{
		collide.bottom_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.left, pos) < 2)
	{
		collide.left_bool = 1;
		return ;
	}
	if (ft_size_vec_plane(&plane, collide.right, pos) < 2)
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
	if (ft_dot_product(player->collide.top, vec) < FOV_COS && dist <= FOV_DIST)
	{
		ft_check_collide(sprite->plane, player->collide, player->position);
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
	return (0);
}

int		ft_keyrelease(int keycode, t_game *game)
{
	if (keycode == DESTROY)
		return (ft_trash_game(game));
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
	return (0);
}

int		ft_update_player(t_game *game, t_player *player)
{
	if (player->control.right)
	{
		game->player->angle_z += -ROTATE_SPEED * game->delta_time;
		ft_rotate_vectors_collides(game->player, -ROTATE_SPEED * game->delta_time);
	}
	else if (player->control.left)
	{
		game->player->angle_z += ROTATE_SPEED * game->delta_time;
		ft_rotate_vectors_collides(game->player, ROTATE_SPEED * game->delta_time);
	}
	if (player->control.up)
		game->player->angle_x += -ROTATE_SPEED * game->delta_time;
	else if (player->control.down)
		game->player->angle_x += ROTATE_SPEED * game->delta_time;
	if (player->control.a)
		ft_translation_vector(game, -SPEED_MAX * game->delta_time, 0);
	else if (player->control.d)
		ft_translation_vector(game, SPEED_MAX * game->delta_time, 0);
	if (player->control.w)
		ft_translation_vector(game, -SPEED_MAX * game->delta_time, M_PI / 2);
	else if (player->control.s)
		ft_translation_vector(game, -SPEED_MAX * game->delta_time, -M_PI / 2);
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
	mlx_hook(game->window, 2, 0, ft_keypress, game);
	mlx_hook(game->window, 3, 1, ft_keyrelease, game);
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

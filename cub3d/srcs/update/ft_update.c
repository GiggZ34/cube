/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:43:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/04 15:30:05 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_search_sprites(t_sprite *sprite, t_list **begin, t_player *player)
{
	t_vector	vec;
	t_list		*lst;
	int			dist;

	vec = ft_create_vector(sprite->position, player->position);
	dist = pow(player->position.x - sprite->position.x, 2) +
								pow(player->position.y - sprite->position.y, 2);
	if (ft_dot_product(player->view.view, vec) < FOV_COS && dist <= FOV_DIST)
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
		ft_edit_sprite_plane(sprite, player->position);
		sprite->position.y -= 0.0;
		ft_search_sprites(sprite, &(player->view.sprites_in_fov), player);
		lst_sprites = lst_sprites->next;
	}
	return (0);
}

int		ft_keypress(int keycode, t_game *game)
{
	if (keycode == 53)
		return (mlx_destroy_window(game->mlx, game->window));
	if (keycode == 123)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'z');
	else if (keycode == 124)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'z');
	if (keycode == 125)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, -M_PI / 10, 'x');
	else if (keycode == 126)
		ft_rotate_vectors_view(game, game->player->view.tab_vectors, M_PI / 10, 'x');
	if (keycode == 0)
		ft_translation_vector(game, -0.5, 0);
	else if (keycode == 2)
		ft_translation_vector(game, 0.5, 0);
	if (keycode == 13)
		ft_translation_vector(game, -0.5, M_PI / 2);
	else if (keycode == 1)
		ft_translation_vector(game, -0.5, -M_PI / 2);
	return (0);
}
int		ft_update(t_game *game)
{
	ft_update_sprites(game->lst_sprites, game->player);
	ft_draw(game);
	return (0);
}

int		ft_update_loop(t_game *game)
{
	mlx_hook(game->window, 2, 1L<<0, ft_keypress, game);
	mlx_loop_hook(game->mlx, &ft_update, game);
	mlx_loop(game->mlx);
	return (0);
}

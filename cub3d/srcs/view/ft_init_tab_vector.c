/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tab_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:26:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 16:23:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_vector_to_tab(t_game *game, t_dot dot, int id)
{
	int			i;
	t_dot		pos;

	pos = game->player.position;
	id *= game->screen.size;
	i = -1;
	while (++i < game->screen.size)
	{
		dot.x += game->screen.w_vec;
		game->player.view.tab_vectors[id + i] = ft_create_vector(pos, dot);
	}
}

static void	ft_init_vector_collides(t_player *player, t_vector normal)
{
	player->collide.top = normal;
	player->collide.bottom = ft_rotate_vector(normal, M_PI, 'z');
	player->collide.right = ft_rotate_vector(normal, M_PI / 2, 'z');
	player->collide.left = ft_rotate_vector(normal, 3 * M_PI / 2, 'z');
}

int	ft_init_tab_vector(t_game *game, t_dot origin)
{
	int			id;
	int			size;

	ft_screen(game);
	ft_bzero(&(game->player.view.view), sizeof(t_vector));
	game->player.view.view.y = -1;
	game->player.view.view = ft_rotate_vector(game->player.view.view,
			game->player.angle_z, 'z');
	ft_init_vector_collides(&game->player, game->player.view.view);
	origin.y -= 1;
	origin.x -= game->screen.w_vec * game->screen.size / 2;
	origin.z += game->screen.h_vec * game->screen.height / 2;
	size = game->screen.size * game->screen.height;
	game->player.view.tab_vectors = ft_calloc(sizeof(t_vector), size);
	if (!game->player.view.tab_vectors)
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	id = -1;
	while (++id < game->screen.height)
	{
		ft_vector_to_tab(game, origin, id);
		origin.z -= game->screen.h_vec;
	}
	return (0);
}

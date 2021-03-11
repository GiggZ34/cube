/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 21:39:58 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_drawing_scale(t_game *game, int id, int color)
{
	int	i;
	int	j;
	int	pos;

	i = -1;
	while (++i < game->screen.scale)
	{
		j = -1;
		while (++j < game->screen.scale)
		{
			pos = id + i * game->screen.size + j;
			game->screen.color[pos] = color;
		}
	}
}

void	*ft_draw(void *g)
{
	t_thread	*thread;
	int			id;
	int			i;
	int			j;
	t_vector	vec;

	thread = (t_thread *)g;
	i = thread->start;
	while (i < thread->start + thread->size)
	{
		j = 0;
		while (j < thread->game->screen.height)
		{
			id = j * thread->game->screen.size + i;
			vec = thread->game->player->view.tab_vectors[id];
			if (thread->game->player->angle_x != 0)
				vec = ft_rotate_vector(vec, thread->game->player->angle_x, 'x');
			if (thread->game->player->angle_y != 0)
				vec = ft_rotate_vector(vec, thread->game->player->angle_y, 'y');
			if (thread->game->player->angle_z != 0)
				vec = ft_rotate_vector(vec, thread->game->player->angle_z, 'z');
			if (thread->game->player->view.sprites_in_fov)
				ft_drawing_scale(thread->game, id, ft_pixel_color(thread->game, vec, thread->game->player->view.sprites_in_fov->content));
			else
				ft_drawing_scale(thread->game, id, ft_pixel_color(thread->game, vec, NULL));
			j += thread->game->screen.scale;
		}
		i += thread->game->screen.scale;
	}
	return (0);
}

void	ft_draw_multi_threads(t_game *game)
{
	int			i;
	int			size_px;
	t_thread	thread[NB_THREADS];

	size_px = game->screen.size / NB_THREADS;
	i = -1;
	while (++i < NB_THREADS)
	{
		thread[i].game = game;
		thread[i].start = size_px * i;
		thread[i].size = size_px;
		if (pthread_create(&thread[i].thread, NULL, ft_draw, (&thread[i])))
			exit(1);
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(thread[i].thread, NULL);
	i = -1;
	while (++i < NB_THREADS)
		pthread_detach(thread[i].thread);
	ft_print_fps(game, game->dt.dt_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 16:45:42 by grivalan         ###   ########lyon.fr   */
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

t_vector	ft_rotate_vector_current(t_game *game, t_vector vec)
{
	if (game->player.angle_x != 0)
		vec = ft_rotate_vector(vec, game->player.angle_x, 'x');
	if (game->player.angle_y != 0)
		vec = ft_rotate_vector(vec, game->player.angle_y, 'y');
	if (game->player.angle_z != 0)
		vec = ft_rotate_vector(vec, game->player.angle_z, 'z');
	return (vec);
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
			if (thread->screen->color[id] == UNVISIBLE_COLOR)
			{
				vec = thread->game->player.view.tab_vectors[id];
				vec = ft_rotate_vector_current(thread->game, vec);
				if (thread->game->player.view.sprites_in_fov)
					ft_drawing_scale(thread->game, id, ft_pixel_color(thread->game,
						vec, thread->game->player.view.sprites_in_fov->content));
				else
					ft_drawing_scale(thread->game, id,
									ft_pixel_color(thread->game, vec, NULL));
			}
			j += thread->game->screen.scale;
		}
		i += thread->game->screen.scale;
	}
	pthread_exit(&thread->thread);
	return (0);
}

void	ft_draw_multi_threads(t_game *game, t_screen *gun)
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
		thread[i].screen = gun;
		if (pthread_create(&thread[i].thread, NULL, ft_draw, (&thread[i])))
			exit(1);
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(thread[i].thread, NULL);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, game->window);
	if (mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0))
		ft_trash_game(game, put_image_fail, -1);
	if (mlx_put_image_to_window(game->mlx, game->window, game->player.arm->ptr, 0, 0))
		ft_trash_game(game, put_image_fail, -1);
	ft_print_fps(game, game->dt.dt_str);
}

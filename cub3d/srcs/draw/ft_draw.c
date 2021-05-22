/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:47:03 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_drawing_scale(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	id;
	int	pos;

	i = -1;
	id = y * game->screen.size + x;
	while (++i < game->screen.scale && y + i < game->screen.height)
	{
		j = -1;
		while (++j < game->screen.scale && x + i < game->screen.size)
		{
			pos = id + i * game->screen.size + j;
			game->screen.color[pos] = color;
		}
	}
}

static void	draw_column(t_thread *thread, int column)
{
	int			j;
	int			id;
	t_vector	vec;

	j = 0;
	while (j < thread->game->screen.height)
	{
		id = j * thread->game->screen.size + column;
		vec = thread->game->player.view.tab_vectors[id];
		if (thread->screen->color[id] == INVISIBLE_COLOR)
		{
			vec = ft_rotate_vector(vec, thread->game->player.angle_x, 'x');
			vec = ft_rotate_vector(vec, thread->game->player.angle_z, 'z');
			ft_drawing_scale(thread->game, column, j,
				ft_pixel_color(thread->game, &vec, thread->sprite));
		}
		else
			ft_drawing_scale(thread->game, column, j,
				luminosity_px(thread->game, thread->screen->color[id],
					thread->game->player.position));
		j += thread->game->screen.scale;
	}
}

static void	*ft_draw(void *g)
{
	t_thread	*thread;
	int			i;

	thread = (t_thread *)g;
	i = thread->start;
	while (i < thread->game->screen.width && i < thread->start + thread->size)
	{
		draw_column(thread, i);
		i += thread->game->screen.scale;
	}
	pthread_exit(&thread->thread);
}

static void	screen_shot(t_game *game)
{
	if (game->save_picture)
	{
		if (ft_image_save(game) < 54)
			ft_trash_game(game, image_not_exist, -1, "failed create img");
		game->save_picture = 0;
		if (game->exit)
			ft_trash_game(game, succes, -1, "Image create !\n");
	}
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
		ft_bzero(&(thread[i]), sizeof(t_thread));
		if (game->player.view.sprites_in_fov)
			thread[i].sprite = game->player.view.sprites_in_fov->content;
		thread[i].game = game;
		thread[i].start = size_px * i;
		thread[i].size = size_px;
		thread[i].screen = gun;
		if (pthread_create(&thread[i].thread, NULL, ft_draw, (&thread[i])))
			ft_trash_game(game, allocation_fail, game->file.fd, "\n");
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(thread[i].thread, NULL);
	screen_shot(game);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->screen.ptr, 0, 0);
	ft_print_fps(game, game->dt.dt_str, game->dt.scale_str);
}

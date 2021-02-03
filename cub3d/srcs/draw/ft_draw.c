/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 12:39:04 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_search_color(t_texture *texture, t_dot dot, t_plane plane)
{
	int i;
	int j;

	j = 0;
	if (!texture)
		return (0);
	if (plane.a == 1)
	{
		dot.y -= (int)dot.y;
		j = texture->width * dot.y;
	}
	else if (plane.b == 1)
	{
		dot.x -= (int)dot.x;
		j = texture->width * dot.x;
	}
	dot.z -= (int)dot.z;
	i = texture->height * dot.z;
	return (texture->color[i][j]);
}

static t_wall		*ft_wall_inter(t_list *lst, t_vector v, t_dot pos, t_dot *mem)
{
	t_wall	*wall;
	t_wall	*wall_mem;
	t_dot	inter_dot;
	double	size_mem;
	double	size;

	size_mem = -1;
	wall_mem = NULL;
	while (lst)
	{
		wall = lst->content;
		size = ft_size_vec_plane(&(wall->plane), v, pos);
		inter_dot = ft_intersect_plane_dot(pos, v, size);
		if ((size >= 0 && (size < size_mem || size_mem == -1))
			&& (inter_dot.z >= 0 && inter_dot.z <= 1)
			&& ((wall->plane.a == 1 && (wall->pos.y <= inter_dot.y
							&& wall->pos.y + wall->width > inter_dot.y))
			|| (wall->plane.b == 1 && (wall->pos.x <= inter_dot.x
							&& wall->pos.x + wall->width > inter_dot.x))))
		{
			wall_mem = wall;
			size_mem = size;
			*mem = inter_dot;
		}
		if (!wall_mem && size >= 0 && (inter_dot.z < 0 || inter_dot.z > 1))
			*mem = inter_dot;
		lst = lst->next;
	}
	return (wall_mem);
}

static int		ft_color_dot(t_game *game, t_vector vec)
{
	t_player	*player;
	t_wall		*wall;
	t_dot		dot;

	player = game->player;
	wall = ft_wall_inter(player->view.lst_walls, vec, player->position, &dot);
	if (dot.z > 1)
		return (game->file->ground_color);
	else if (dot.z < 0)
		return (game->file->sky_color);
	else if (wall)
		return (ft_search_color(wall->texture, dot, wall->plane));
	return (0);
}

int				ft_draw(t_game *game)
{
	int			x;
	int			y;
	t_vector	vec;

	y = -1;
	while (++y < game->screen.height)
	{
		x = -1;
		while (++x < game->screen.width)
		{
			vec = game->player->view.tab_vectors[y * game->screen.width + x];
			mlx_pixel_put(game->mlx, game->window, x, y, ft_color_dot(game, vec));
		}
	}
	return (0);
}

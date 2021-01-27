/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:26:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/26 10:19:45 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_search_color(t_texture *texture, t_dot dot)
{
	double i;
	double j;

	dot.x -= (int)dot.x;
	j = texture->width * dot.x;
	dot.z -= (int)dot.z;
	i = texture->height * dot.z;
	if (texture)
	{
		return (255);
		return (texture->color[(int)i][(int)j]);
	}
	return (0);
}

double		ft_size_vec_wall(t_wall *p, t_vector vec, t_dot orign)
{
	double	fac;

	if ((fac = p->a * vec.x + p->b * vec.y + p->c * vec.z) == 0)
		return (-1);
	return (-(p->a * orign.x + p->b * orign.y + p->c * orign.z + p->d) / fac);
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
		size = ft_size_vec_wall(wall, v, pos);
		inter_dot = ft_intersect_plane_dot(pos, v, size);
		if (size >= 0 && (size_mem > size || size_mem < 0))
		{
			if (inter_dot.z >= 0 && inter_dot.z <= 1)
			{
				wall_mem = wall;
				size_mem = size;
				*mem = inter_dot;
			}
			*mem = inter_dot;
		}
		lst = lst->next;
	}
	return (wall_mem);
}

static int		ft_color_dot(t_game *game, t_vector vec)
{
	t_player	*player;
	t_wall		*wall;
	t_dot		inter_dot;

	player = game->player;
	wall = ft_wall_inter(game->lst_walls, vec, player->position, &inter_dot);
	if (inter_dot.z > 1)
		return (game->file->ground_color);
	else if (inter_dot.z < 0)
		return (game->file->sky_color);
	else if (wall)
		return (ft_search_color(wall->add, inter_dot));
	return (0);
}

int				ft_draw(t_game *game)
{
	double		i;
	double		j;
	int			px_w;
	int			px_h;
	t_vector	vec;

	i = 0;
	px_h = 0;

	while (i <= game->screen->height_fov)
	{
		vec = game->player->view;
		px_w = 0;
		j = 0;
		while (j >= -FOV)
		{
			mlx_pixel_put(game->mlx, game->window, px_w, px_h, ft_color_dot(game, vec));
			px_w++;
			j -= FOV / game->screen->width;
			vec = ft_rotate_vector(vec, j, 'z');
		}
		px_h++;
		i += game->screen->height_fov / game->screen->height;
		vec = ft_rotate_vector(vec, i, 'x');
	}
	return (0);
}

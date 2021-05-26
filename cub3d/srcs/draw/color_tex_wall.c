/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tex_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:59:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/23 15:47:52 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*init_px_pos(t_plane *plane, t_vector *v, t_dot *dot, int *pos)
{
	pos = calloc(sizeof(int), 2);
	if (!pos)
		return (NULL);
	if (plane->a != 0)
		pos[0] = ft_abs(plane->d);
	else
		pos[0] = floor(ft_abs((*dot).x));
	if (plane->b != 0)
		pos[1] = ft_abs(plane->d);
	else
		pos[1] = floor(ft_abs((*dot).y));
	if (plane->a != 0 && v->x < 0)
		pos[0]--;
	if (plane->b != 0 && v->y < 0)
		pos[1]--;
	return (pos);
}

double	ft_is_wall(t_game *g, t_plane *plane, t_vector *v, t_dot *dot)
{
	double	size;
	int		*pos;

	pos = NULL;
	size = plane->nom_size / (plane->a * v->x + plane->b * v->y);
	dot->x = g->player.position.x + v->x * size;
	dot->y = g->player.position.y + v->y * size;
	dot->z = g->player.position.z + v->z * size;
	if (dot->z < 0 || dot->z > 1)
		return (-1);
	pos = init_px_pos(plane, v, dot, pos);
	if (pos[0] >= 0 && pos[1] >= 0 && pos[1] < g->file.height_map
		&& pos[0] < (int)ft_strlen(g->file.map[pos[1]])
		&& g->file.map[pos[1]][pos[0]] == '1')
		return (size);
	return (-1);
}

int	ft_is_in_wall(t_texture *texture, t_dot inter, char dir)
{
	int	x;
	int	y;

	y = texture->height - (texture->height * inter.z);
	if (dir == 'y')
		x = texture->width * (inter.x - floor(inter.x));
	else
		x = texture->width * (inter.y - floor(inter.y));
	return ((texture->color[y * texture->size_line + x]));
}

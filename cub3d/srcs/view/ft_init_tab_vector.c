/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tab_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:26:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 12:26:40 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_vector_to_tab(t_game *game, t_vector vec, double angle, int id)
{
	int			i;

	id *= game->screen.width;
	i = -1;
	while (++i < game->screen.width)
	{
		vec = ft_rotate_vector(vec, angle, 'z');
		game->player->view.tab_vectors[id + i] = vec;
	}
}

int			ft_init_tab_vector(t_game *game, t_vector vec)
{
	int		id;
	int		size;
	double	angle_x;
	double	angle_z;

	ft_screen(game);
	size = game->screen.width * game->screen.height;
	angle_z = ft_deg_to_rad(-(FOV / 2));
	vec = ft_rotate_vector(vec, angle_z, 'z');
	angle_x = ft_deg_to_rad(game->screen.height_fov / 2);
	vec = ft_rotate_vector(vec, angle_x, 'x');
	angle_x = -(ft_deg_to_rad(game->screen.height_fov / game->screen.height));
	angle_z = ft_deg_to_rad(FOV / game->screen.width);
	if (!(game->player->view.tab_vectors = ft_calloc(sizeof(t_vector), size)))
		return (game->file->error_code = 3);
	id = -1;
	while (++id < game->screen.height)
	{
		ft_vector_to_tab(game, vec, angle_z, id);
		vec = ft_rotate_vector(vec, angle_x, 'x');
	}
	return (0);
}

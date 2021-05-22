/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tex_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:59:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 18:59:48 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_intensity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:27:22 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/23 15:27:31 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	luminosity_px(t_game *game, int color, t_dot collide)
{
	float		rgb[6];
	int			i;

	rgb[3] = game->file.light_color[0] * 80;
	rgb[4] = game->file.light_color[1] * 80;
	rgb[5] = game->file.light_color[2] * 80;
	if (!game->debug)
		return (color);
	if (color == INVISIBLE_COLOR)
		return (INVISIBLE_COLOR);
	i = -1;
	while (++i < 3)
		rgb[i] = ((unsigned char)(color >> (i * 8))) * 0.00392156862;
	check_light(game, collide, rgb);
	i = -1;
	while (++i < 3)
		rgb[i] *= rgb[i + 3];
	return (ft_color_generate((unsigned char)rgb[2], (unsigned char)rgb[1],
			(unsigned char)rgb[0], 0));
}

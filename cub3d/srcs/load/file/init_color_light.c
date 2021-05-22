/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:28:35 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 15:08:09 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_color_light(t_game *game, float red, float green, float blue)
{
	game->file.light_color[0] = blue / 255;
	game->file.light_color[1] = green / 255;
	game->file.light_color[2] = red / 255;
}

void	ft_init_light(t_game *game, int x, int y)
{
	t_light	*light;
	t_light	*tmp;

	light = ft_calloc(sizeof(t_light), 1);
	light->type = 'L';
	light->x = x + 0.5;
	light->y = y + 0.5;
	light->z = 0.7;
	light->rgb[0] = game->file.light_color[0];
	light->rgb[1] = game->file.light_color[1];
	light->rgb[2] = game->file.light_color[2];
	if (!game->light)
		game->light = light;
	else
	{
		tmp = game->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
}

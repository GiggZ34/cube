/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:26:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 12:28:44 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_light(t_game *game)
{
	t_light	*tmp;

	while (game->light)
	{
		tmp = game->light;
		game->light = game->light->next;
		if (tmp->t)
			free(tmp->t);
		free(tmp);
	}
	game->light = NULL;
}

void	*free_with_protect(void *content)
{
	if (content)
		free(content);
	return (NULL);
}

void	delete(void *content)
{
	if (content)
		free(content);
	content = NULL;
}

int	ft_free_hud(t_game *g, t_player *p)
{
	int	i;
	int	j;
	int	nb_frame;

	if (p->gun)
	{
		i = -1;
		while (++i < nb_anim)
		{
			nb_frame = ft_define_nb_anim(i);
			j = -1;
			while (++j < nb_frame)
				mlx_destroy_image(g->mlx, p->gun[i][j].ptr);
			free(p->gun[i]);
			p->gun[i] = NULL;
		}
		free(p->gun);
		p->gun = NULL;
	}
	return (0);
}

void	*free_texture(t_game *game, t_texture *texture)
{
	if (texture)
	{
		if (mlx_destroy_image(game->mlx, texture->ptr))
			printf("Error\nTexture destruction failed\n");
		free(texture);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:59:04 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/08 15:54:08 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_modif_nom_size(t_list *lst, t_dot pos)
{
	t_plane	*plane;

	while (lst)
	{
		plane = lst->content;
		plane->nom_size = -(plane->a * pos.x + plane->b * pos.y + plane->d);
		lst = lst->next;
	}
}

void	ft_update_planes(t_game *game)
{
	ft_modif_nom_size(game->lst_planes_left, game->player.position);
	ft_modif_nom_size(game->lst_planes_bottom, game->player.position);
	ft_modif_nom_size(game->lst_planes_right, game->player.position);
	ft_modif_nom_size(game->lst_planes_top, game->player.position);
	game->sky_ground.ground_plane.nom_size = ft_plane_inter_nom(
			&game->sky_ground.ground_plane, game->player.position);
	game->sky_ground.sky_plane.nom_size = ft_plane_inter_nom(
			&game->sky_ground.sky_plane, game->player.position);
}

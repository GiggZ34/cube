/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_inter_nom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:54:57 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/27 13:56:28 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_plane_inter_nom(t_plane *p, t_dot pos)
{
	p->nom_size = -(p->a * pos.x + p->b * pos.y + p->c * pos.z + p->d);
	return (p->nom_size);
}

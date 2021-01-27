/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_vec_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:39:35 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/21 11:33:11 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_size_vec_plane(t_plane *p, t_vector vec, t_dot orign)
{
	double	fac;

	if ((fac = p->a * vec.x + p->b * vec.y + p->c * vec.z) == 0)
		return (-1);
	return (-(p->a * orign.x + p->b * orign.y + p->c * orign.z + p->d) / fac);
}

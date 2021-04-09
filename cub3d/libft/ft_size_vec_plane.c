/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_vec_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:39:35 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/07 10:58:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_size_vec_plane(t_plane *p, t_vector vec, float nom)
{
	double	fac;

	fac = p->a * vec.x + p->b * vec.y + p->c * vec.z;
	if (!fac)
		return (-1);
	return (nom / fac);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane_dot.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:01:15 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/21 11:31:30 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dot	ft_intersect_plane_dot(t_dot origin, t_vector vec, double t)
{
	t_dot result;

	result.x = origin.x + vec.x * t;
	result.y = origin.y + vec.y * t;
	result.z = origin.z + vec.z * t;
	return (result);
}

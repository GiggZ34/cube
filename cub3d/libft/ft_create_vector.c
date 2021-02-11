/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:41:34 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/04 09:39:25 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_create_vector(t_dot dot1, t_dot dot2)
{
	t_vector	normalize_vector;
	double		n;

	normalize_vector.x = dot2.x - dot1.x;
	normalize_vector.y = dot2.y - dot1.y;
	normalize_vector.z = dot2.z - dot1.z;
	n = sqrt(pow(normalize_vector.x, 2) + pow(normalize_vector.y, 2)
						+ pow(normalize_vector.z, 2));
	normalize_vector.x /= n;
	normalize_vector.y /= n;
	normalize_vector.z /= n;
	return (normalize_vector);
}

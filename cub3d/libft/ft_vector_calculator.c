/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_calculator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:41:34 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/20 13:56:55 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_normal_vector_calculator(t_dot dot1, t_dot dot2)
{
	t_vector	normal_vector;
	double		n;

	normal_vector.x = dot2.x - dot1.x;
	normal_vector.y = dot2.y - dot1.y;
	normal_vector.z = dot2.z - dot1.z;
	n = sqrt(pow(normal_vector.x, 2) + pow(normal_vector.y, 2)
						+ pow(normal_vector.z, 2));
	normal_vector.x /= n;
	normal_vector.y /= n;
	normal_vector.z /= n;
	return (normal_vector);
}

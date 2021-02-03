/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:33:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/02 15:19:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_rotate_on_x(t_vector vec, double rad)
{
	t_vector	result;

	result.x = vec.x;
	result.y = vec.y * cos(rad) - vec.z * sin(rad);
	result.z = vec.y * sin(rad) + vec.z * cos(rad);
	return (result);
}

t_vector	ft_rotate_on_y(t_vector vec, double rad)
{
	t_vector	result;

	result.x = vec.z * sin(rad) + vec.x * cos(rad);
	result.y = vec.y;
	result.z = vec.z * cos(rad) - vec.x * sin(rad);
	return (result);
}

t_vector	ft_rotate_on_z(t_vector vec, double rad)
{
	t_vector	result;

	result.x = vec.x * cos(rad) - vec.y * sin(rad);
	result.y = vec.x * sin(rad) + vec.y * cos(rad);
	result.z = vec.z;
	return (result);
}

t_vector	ft_rotate_vector(t_vector vec, double rad, char axis)
{
	if (axis == 'x')
		return (ft_rotate_on_x(vec, rad));
	else if (axis == 'y')
		return (ft_rotate_on_y(vec, rad));
	else if (axis == 'z')
		return (ft_rotate_on_z(vec, rad));
	return (vec);
}

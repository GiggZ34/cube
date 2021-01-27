/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:33:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/22 10:20:04 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_rotate_on_x(t_vector vec, double angle)
{
	vec.y = vec.y * cos(angle) - vec.z * sin(angle);
	vec.z = vec.y * sin(angle) + vec.z * cos(angle);
	return (vec);
}

t_vector	ft_rotate_on_y(t_vector vec, double angle)
{
	vec.z = vec.z * cos(angle) - vec.x * sin(angle);
	vec.x = vec.z * sin(angle) + vec.x * cos(angle);
	return (vec);
}

t_vector	ft_rotate_on_z(t_vector vec, double angle)
{
	vec.x = vec.x * cos(angle) - vec.y * sin(angle);
	vec.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (vec);
}

t_vector	ft_rotate_vector(t_vector vec, double angle, char axis)
{
	if (axis == 'x')
		return (ft_rotate_on_x(vec, angle));
	else if (axis == 'y')
		return (ft_rotate_on_y(vec, angle));
	else if (axis == 'z')
		return (ft_rotate_on_z(vec, angle));
	return (vec);
}

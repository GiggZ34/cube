/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:41:34 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/28 12:23:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_create_vector(t_dot dot1, t_dot dot2)
{
	t_vector	vector;

	vector.x = dot2.x - dot1.x;
	vector.y = dot2.y - dot1.y;
	vector.z = dot2.z - dot1.z;
	return (ft_normalize_vector(vector));
}

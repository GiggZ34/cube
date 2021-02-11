/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scalar_product.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:15:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/03 13:26:08 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_scalar_product(t_vector *vec1, t_vector *vec2)
{
	t_vector	result;

	result.x = 0;
	result.y = 0;
	result.z = 0;
	if (vec1 && vec2)
	{
		result.x = vec1->x * vec2->x;
		result.y = vec1->y * vec2->y;
		result.z = vec1->z * vec2->z;
	}
	return (result);
}

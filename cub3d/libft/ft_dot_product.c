/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:15:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/28 11:15:18 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_dot_product(t_vector vec1, t_vector vec2)
{
	double	result;

	result = vec1.x * vec2.x;
	result += vec1.y * vec2.y;
	result += vec1.z * vec2.z;
	return (result);
}

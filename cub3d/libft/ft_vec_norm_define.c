/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_norm_define.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:15:40 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/07 14:21:42 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vec_norm_define(t_vector vec, double size)
{
	vec.x *= size;
	vec.y *= size;
	vec.z *= size;
	return (vec);
}

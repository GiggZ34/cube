/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:10:50 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/02 11:42:56 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_color_generate(int red, int green, int blue, int alpha)
{
	return (256 * 256 * 256 * alpha + 256 * 256 * red + 256 * green + blue);
}

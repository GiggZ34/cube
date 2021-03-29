/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decbin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:26:21 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/29 16:39:32 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_decbin(char **bin, long long dec)
{
	int	nb_bits;
	int	id;

	nb_bits = 0;
	if (dec < 0)
		dec *= -1;
	while (dec - (long long)pow(2, nb_bits) >= dec / 2)
		nb_bits++;
	(*bin) = ft_calloc(nb_bits + 2, 1);
	if (!(*bin))
		return (1);
	id = nb_bits;
	while (nb_bits >= 0)
	{
		if (dec - (long long)pow(2, nb_bits) >= 0)
		{
			(*bin)[id - nb_bits] = '1';
			dec -= (long long)pow(2, nb_bits);
		}
		else
			(*bin)[id - nb_bits] = '0';
		nb_bits--;
	}
	return (0);
}

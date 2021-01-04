/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:42:42 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:14:23 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in_array(const char c, const char *charset)
{
	int i;

	i = -1;
	while (charset[++i])
	{
		if (c == charset[i])
			return (i);
	}
	return (-1);
}

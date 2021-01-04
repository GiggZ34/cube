/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:38:42 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:15:52 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	s2 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == (unsigned char)c)
			return (&s2[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:58:08 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:42:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char				*d;
	const unsigned char	*s;
	unsigned char		c2;
	size_t				i;

	d = dst;
	s = src;
	c2 = c;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (i == 0 || s[i - 1] != c2))
	{
		d[i] = s[i];
		i++;
	}
	if (n == i && s[i - 1] != c2)
		return (0);
	else
		return (&d[i]);
}

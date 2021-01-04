/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:20:02 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:18:01 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s_1;
	unsigned char	*s_2;

	s_1 = (unsigned char*)s1;
	s_2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (s_1[i] == s_2[i] && i < n - 1 && s_1[i] && s_2[i])
		i++;
	return (s_1[i] - s_2[i]);
}

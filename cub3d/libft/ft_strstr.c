/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:09:42 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/29 14:31:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *s, char *needle)
{
	int i;

	if (!s)
		return (0);
	if (!needle)
		return (s);
	while (*s)
	{
		i = 0;
		while (s[i] == needle[i])
		{
			if (!needle[++i])
				return (s);
		}
		s++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repeat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:04:35 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:16:54 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_repeat(const char *str, int nb)
{
	char	*new_str;
	int		i;
	int		y;

	if (!(new_str = malloc(sizeof(char) * (nb * ft_strlen(str) + 1))))
		return (0);
	y = 0;
	while (nb > 0)
	{
		i = -1;
		while (str[++i])
		{
			new_str[y] = str[i];
			y++;
		}
		nb--;
	}
	new_str[y] = '\0';
	return (new_str);
}

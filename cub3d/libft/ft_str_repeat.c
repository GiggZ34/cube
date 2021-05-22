/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repeat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:04:35 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:51:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_repeat(const char *str, int nb)
{
	char	*new_str;
	int		i;
	int		y;

	new_str = calloc(sizeof(char), (nb * ft_strlen(str) + 1));
	if (!(new_str))
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
	return (new_str);
}

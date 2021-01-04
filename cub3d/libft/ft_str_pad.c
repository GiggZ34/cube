/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_pad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:35:01 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:33:37 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_def_direction(int *size, char *c, char direction)
{
	if (*size < 0)
	{
		(*size) *= -1;
		*c = ' ';
		if (direction == 'r')
			return ('l');
		else
			return ('r');
	}
	return (direction);
}

char		*ft_str_pad(char *src, int size, char c, char direction)
{
	char	*new_str;
	int		position;

	direction = ft_def_direction(&size, &c, direction);
	if (!src)
		return (0);
	else if ((int)ft_strlen(src) >= size)
		return (src);
	if (!(new_str = malloc(sizeof(char) * (size + 1))))
		return (0);
	new_str[size] = '\0';
	ft_memset(new_str, c, size);
	if (direction == 'r')
		position = size - ft_strlen(src);
	else if (direction == 'c')
		position = (size / 2) - (ft_strlen(src) / 2);
	else
		position = 0;
	new_str = ft_strcpypos(new_str, src, position);
	free(src);
	return (new_str);
}

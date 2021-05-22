/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_pad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:35:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:51:15 by grivalan         ###   ########lyon.fr   */
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

char	*ft_str_pad(char *src, int size, char c, char direction)
{
	char	*new_str;
	int		position;

	direction = ft_def_direction(&size, &c, direction);
	if (!src)
		return (0);
	else if ((int)ft_strlen(src) >= size)
		return (src);
	new_str = calloc(sizeof(char), (size + 1));
	if (!new_str)
		return (0);
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

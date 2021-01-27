/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:35:44 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/31 11:31:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, int size)
{
	int		len;
	char	*new_str;
	int		i;

	if (size <= 0)
		return (str);
	len = ft_strlen(str) + size + 1;
	if (!(new_str = ft_calloc(sizeof(char), len)))
		return (0);
	if (str)
	{
		i = -1;
		while (str[++i])
			new_str[i] = str[i];
		free(str);
	}
	return (new_str);
}
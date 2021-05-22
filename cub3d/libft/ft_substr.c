/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:12:08 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:58:23 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*new_str;
	int		i;
	int		j;
	int		strlen;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (start < 0)
		start = strlen + start;
	if (start > strlen)
		len = 0;
	else if (strlen < len)
		len = strlen - start;
	new_str = calloc(sizeof(char), len + 1);
	if (!new_str)
		return (0);
	i = start;
	j = 0;
	while (j < strlen && i < (start + len) && s[i])
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

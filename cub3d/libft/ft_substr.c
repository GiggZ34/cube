/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:12:08 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:18:23 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	strlen;

	if (!s)
		return (0);
	if (start > (strlen = ft_strlen(s)))
		len = 0;
	else if (strlen < len)
		len = strlen - start;
	if ((new_str = malloc(sizeof(char) * len + 1)) == NULL)
		return (0);
	i = start;
	j = 0;
	while (j < strlen && i < (start + len) && s[i])
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

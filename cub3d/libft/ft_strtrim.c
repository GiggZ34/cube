/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:57:14 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:18:18 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_in_set(const char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		start;
	int		end;
	int		len;
	int		j;

	if (!set || !s1)
		return (0);
	start = 0;
	end = (int)ft_strlen(s1) - 1;
	while (s1[start] && ft_in_set(s1[start], set))
		start++;
	while (end > 0 && ft_in_set(s1[end], set))
		end--;
	len = end - start + 1;
	if (len <= 0)
		len = 0;
	if ((new_str = malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	j = 0;
	while (j <= len && s1[start] && start <= end)
		new_str[j++] = s1[start++];
	new_str[j] = '\0';
	return (new_str);
}

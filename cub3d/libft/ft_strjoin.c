/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:37:48 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:17:31 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s1 || !s2)
		return (0);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	if ((new_str = malloc(sizeof(char) * (len1 + len2 + 1))) == NULL)
		return (0);
	len1 = -1;
	while (s1[++len1])
		new_str[len1] = s1[len1];
	len2 = -1;
	while (s2[++len2])
		new_str[len1++] = s2[len2];
	new_str[len1] = '\0';
	return (new_str);
}

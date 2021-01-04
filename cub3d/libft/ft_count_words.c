/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:12:19 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/29 12:48:02 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, const char *charset)
{
	if (!c)
		return (1);
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

int			ft_count_words(const char *s, const char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_is_charset(s[i], charset) && ft_is_charset(s[i + 1], charset))
			count++;
		i++;
	}
	return (count);
}

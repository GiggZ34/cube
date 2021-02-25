/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:47:18 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/29 11:42:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_charset(char c, const char *charset)
{
	if (!c)
		return (1);
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

static size_t	ft_letter(char const *s, char *c)
{
	size_t	nb_letters;
	int		i;

	nb_letters = 0;
	i = 0;
	if (ft_is_charset(s[i], c))
		nb_letters++;
	while (s[i] && !ft_is_charset(s[++i], c))
		nb_letters++;
	return (nb_letters + 1);
}

static	int		ft_free_split(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	free(str);
	return (0);
}

static int		ft_str_to_tab(char **new_s, char *str, char *c, size_t nb_words)
{
	size_t i;
	size_t j;

	i = -1;
	while (++i < nb_words)
	{
		while (*str && ft_is_charset(*str, c))
			str++;
		if ((new_s[i] = malloc(sizeof(char) * (ft_letter(str, c) + 1))) == NULL)
			return (ft_free_split(new_s));
		j = 0;
		while (*str && !ft_is_charset(*str, c))
			new_s[i][j++] = *str++;
		new_s[i][j] = '\0';
	}
	return (0);
}

char			**ft_split(char const *s, char *c)
{
	char	**new_s;
	char	*str;
	size_t	nb_words;

	if (!s)
		return (0);
	str = (char*)s;
	nb_words = ft_count_words(s, c);
	if ((new_s = malloc(sizeof(char *) * (nb_words + 1))) == NULL)
		return (0);
	new_s[nb_words] = 0;
	ft_str_to_tab(new_s, str, c, nb_words);
	return (new_s);
}

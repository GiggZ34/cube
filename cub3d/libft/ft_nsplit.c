/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:44:17 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	**ft_free_tab(int **tab, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		free(tab[i]);
	free(tab);
	return (0);
}

static int	*ft_line_generate(int *tab, int n, int id)
{
	int	*line;
	int	i;

	line = ft_calloc(sizeof(int), n);
	if (!line)
		return (0);
	i = -1;
	while (++i == 0 || i < n)
		line[i] = tab[(id * n) + i];
	return (line);
}

int	**ft_nsplit(int *tab, int tab_size, int n)
{
	int	**split;
	int	len;
	int	id;

	len = tab_size / n;
	split = ft_calloc(sizeof(int *), len);
	if (!split)
		return (0);
	id = -1;
	while (++id < len)
	{
		split[id] = ft_line_generate(tab, n, id);
		if (!split[id])
			return (ft_free_tab(split, id));
	}
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:00 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/11 13:13:30 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	**ft_free_tab(int **tab, int id)
{
	int i;

	i = -1;
	while (++i < id)
		free(tab[i]);
	free(tab);
	return (0);
}

static int	*ft_line_generate(int *tab, int n, int id)
{
	int *line;
	int i;

	if (!(line = ft_calloc(sizeof(int), n)))
		return (0);
	i = -1;
	while (++i == 0 || i < n)
		line[i] = tab[(id * n) + i];
	return (line);
}

int			**ft_nsplit(int *tab, int tab_size, int n)
{
	int	**split;
	int	len;
	int	id;

	len = tab_size / n;
	if (!(split = ft_calloc(sizeof(int *), len)))
		return (0);
	id = -1;
	while (++id < len)
		if (!(split[id] = ft_line_generate(tab, n, id)))
			return (ft_free_tab(split, id));
	return (split);
}

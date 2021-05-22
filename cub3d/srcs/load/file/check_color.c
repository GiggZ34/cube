/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:57:12 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 15:02:21 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_alnum(char *line, int pos)
{
	int	i;

	i = 0;
	if (pos)
		while (line[i] && ft_isdigit(line[i]))
			i++;
	else
		while (line[i] && ft_isalpha(line[i]))
			i++;
	if (line[i] && line[i] != ',' && pos < 4 && pos > 0)
		return (-1);
	return (i);
}

char	**check_color(char *line, char ***array)
{
	int	i;
	int	j;

	(*array) = ft_calloc(sizeof(char *), 4 + 1);
	if (!*array)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < 4)
	{
		if (j - 1 >= 0)
			i += ft_strlen((*array)[j - 1]);
		i += ft_skip_white_space(&(line[i]));
		(*array)[j] = ft_substr(line, i, count_alnum(&(line[i]), j));
		if (!((*array)[j]))
		{
			ft_free_array(*array);
			return (NULL);
		}
		i++;
	}
	return (*array);
}

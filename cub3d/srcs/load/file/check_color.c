/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:57:12 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 19:06:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_number(char *line, int pos)
{
	int	i;

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i] != ',' && pos < 4)
		return (-1);
	return (i);
}

char	**check_color(char *line, char ***array)
{
	int	i;
	int	j;
	int	num;

	(*array) = ft_calloc(sizeof(char *), 4 + 1);
	if (!*array)
		return (NULL);
	i = ft_skip_white_space(line);
	j = 0;
	(*array)[0] = ft_substr(line, i, count_letters(&(line[i])));
	if (!((*array)[j]))
	{
		free(*array);
		return (*array = NULL);
	}
	while (++j < 4)
	{
		i += ft_strlen((*array)[j - 1]);
		i += ft_skip_white_space(&(line[i]));
		num = count_number(&(line[i]), j);
		(*array)[j] = ft_substr(line, i, num);
		if (!((*array)[j]))
		{
			ft_free_array(*array);
			return (*array = NULL);
		}
		i++;
	}
	return (*array);
}

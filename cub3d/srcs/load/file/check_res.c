/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:59:50 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 16:55:58 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**check_res(char *line, char ***array)
{
	int	i;
	int	j;

	*array = ft_split(line, " \t");
	if (!(*array))
		return (NULL);
	j = 0;
	while ((*array)[++j])
	{
		i = -1;
		while ((*array)[j][++i])
		{
			if ((*array)[j][i] != '-' && !ft_isdigit((*array)[j][i]))
			{
				ft_free_array(*array);
				return (*array = NULL);
			}
		}
	}
	return (*array);
}

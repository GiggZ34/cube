/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 19:00:55 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 19:05:36 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**check_texture(char *line, char ***array)
{
	int	i;

	*array = ft_calloc(sizeof(char *), 2 + 1);
	if (!(*array))
		return (NULL);
	i = ft_skip_white_space(line);
	(*array)[0] = ft_substr(line, i, count_letters(&(line[i])));
	if (!(*array)[0])
	{
		free(*array);
		return (*array = NULL);
	}
	i += ft_strlen((*array)[0]);
	i += ft_skip_white_space(&(line[i]));
	(*array)[1] = ft_substr(line, i, ft_strlen(&(line[i])));
	if (!(*array)[1])
	{
		ft_free_array(*array);
		return (*array = NULL);
	}
	return (*array);
}

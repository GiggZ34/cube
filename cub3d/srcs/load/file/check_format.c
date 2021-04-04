/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:54:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 19:05:55 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*type_argument(char *line, char **type)
{
	int		i;

	i = ft_skip_white_space(line);
	if (line[i + 1] != ' ' && line[i + 2] != ' ')
		return (NULL);
	*type = ft_substr(line, i, count_letters(&(line[i])));
	if (!(*type))
		return (NULL);
	return (*type);
}

char	**check_format(char *line, char ***array)
{
	char	*type;

	if (!type_argument(line, &type))
		return (0);
	if (!ft_strncmp(type, "R", 2))
		check_res(line, array);
	else if (!ft_strncmp(type, "F", 2)
		|| !ft_strncmp(type, "C", 2) || !ft_strncmp(type, "L", 2))
		check_color(line, array);
	else
		check_texture(line, array);
	free(type);
	return (*array);
}

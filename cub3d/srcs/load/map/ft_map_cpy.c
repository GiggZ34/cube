/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:19:30 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 15:06:10 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_map_cpy(char **map, int height)
{
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	new_map = ft_calloc(sizeof(char **), height + 1);
	if (!new_map)
		return (NULL);
	new_map[height] = NULL;
	i = -1;
	while (map[++i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map)
		{
			ft_free_array(new_map);
			return (NULL);
		}
	}
	return (new_map);
}

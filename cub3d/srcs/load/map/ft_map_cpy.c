/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:19:30 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/31 12:20:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**ft_map_cpy(char **map, int height)
{
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	if (!(new_map = ft_calloc(sizeof(char**), height + 1)))
		return (NULL);
	new_map[height] = NULL;
	i = -1;
	while (map[++i])
		new_map[i] = ft_strdup(map[i]);
	return (new_map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:06:31 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:53:04 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*scp;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	scp = calloc(sizeof(char), i + 1);
	if (!scp)
		return (0);
	i = -1;
	while (s1[++i])
		scp[i] = s1[i];
	scp[i] = '\0';
	return (scp);
}

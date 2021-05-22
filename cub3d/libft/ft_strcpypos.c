/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpypos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 11:28:51 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:52:22 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpypos(char *dst, char *src, int position)
{
	int	i;

	if (!dst || !src || ft_strlen(dst) - position < ft_strlen(src))
		return (0);
	i = -1;
	while (src[++i])
		dst[position + i] = src[i];
	return (dst);
}

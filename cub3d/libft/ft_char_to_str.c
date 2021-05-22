/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:07:52 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:36:26 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char *) * 2);
	if (!str)
		return (0);
	str[0] = c;
	str[1] = 0;
	return (str);
}

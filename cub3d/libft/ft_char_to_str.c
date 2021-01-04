/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:07:52 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:14:13 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char_to_str(char c)
{
	char *str;

	if (!(str = malloc(sizeof(char *) * 2)))
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

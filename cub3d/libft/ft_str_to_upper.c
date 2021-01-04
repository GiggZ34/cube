/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:28:14 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:17:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_to_upper(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_islower(s[i]))
			s[i] = ft_toupper(s[i]);
	return (s);
}

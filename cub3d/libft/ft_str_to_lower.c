/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:11:08 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:51:59 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_to_lower(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			s[i] = (char)ft_tolower(s[i]);
		i++;
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_white_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 17:23:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/04 17:24:26 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhtespace(str[i]))
		i++;
	return (i);
}

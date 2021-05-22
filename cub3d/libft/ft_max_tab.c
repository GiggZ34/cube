/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:53:47 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:41:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_max_tab(double *tab, int n)
{
	double	result;
	int		i;

	if (n <= 0)
		return (0);
	result = tab[0];
	i = 0;
	while (++i < n)
	{
		if (tab[i] > result)
			result = tab[i];
	}
	return (result);
}

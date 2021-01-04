/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:35:57 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:36:01 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_nb_numbers(long n)
{
	int nb_numbers;

	nb_numbers = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		nb_numbers++;
	while (n != 0)
	{
		n /= 10;
		nb_numbers++;
	}
	return (nb_numbers);
}

static	void	ft_int_to_char(char *str, int id, long n)
{
	if (n > 9)
		ft_int_to_char(str, id - 1, n / 10);
	str[id] = n % 10 + 48;
}

char			*ft_itoa(long n)
{
	char	*result;
	int		i;
	int		size;

	size = ft_nb_numbers(n);
	if ((result = malloc(sizeof(char) * (size + 1))) == NULL)
		return (0);
	ft_memset(result, '0', size + 1);
	result[size] = '\0';
	i = size - 1;
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	ft_int_to_char(result, i, n);
	return (result);
}

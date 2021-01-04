/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:28:32 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/28 12:17:03 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_char(unsigned long nbr, int base)
{
	int count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= base;
		count++;
	}
	return (count);
}

static void	ft_nbr_generation(unsigned long nbr, int id, char *str, char *base)
{
	if (nbr >= ft_strlen(base))
		ft_nbr_generation(nbr / ft_strlen(base), id - 1, str, base);
	str[id] = base[nbr % ft_strlen(base)];
}

char		*ft_itoa_base(unsigned long nbr, char *base)
{
	char	*str;
	int		nb_char;
	int		id;

	nb_char = ft_count_char(nbr, ft_strlen(base));
	if (!(str = malloc(sizeof(char) * (nb_char + 1))))
		return (0);
	ft_memset(str, '0', nb_char);
	str[nb_char] = '\0';
	id = nb_char - 1;
	ft_nbr_generation(nbr, id, str, base);
	return (str);
}

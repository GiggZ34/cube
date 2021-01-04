/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:58:26 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:26:56 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t len;

	len = ft_strlen(s);
	if (s)
	{
		write(fd, s++, len);
		len += write(fd, "\n", 1);
	}
	return (len);
}

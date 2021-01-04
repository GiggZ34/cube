/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:38:58 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/15 19:16:38 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_repeat(char *str, size_t len, int fd)
{
	char	*new_str;
	size_t	str_len;

	new_str = ft_str_repeat(str, len);
	ft_putstr_fd(new_str, fd);
	str_len = ft_strlen(new_str);
	free(new_str);
	return (str_len);
}

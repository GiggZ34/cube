/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_gen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:46:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:34:39 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*file_name_gen(char **name, const char *str, int num, const char *ext)
{
	char	*number;
	int		len_str;
	int		len_num;
	int		len_ext;

	number = ft_itoa(num);
	if (!number)
		return (NULL);
	len_str = ft_strlen(str);
	len_num = ft_strlen(number);
	len_ext = ft_strlen(ext);
	*name = ft_calloc(len_str + len_num + len_ext + 1, sizeof(char));
	if (!(*name))
	{
		free(number);
		return (NULL);
	}
	ft_strcpy((*name), str);
	ft_strcpy(&((*name)[len_str]), number);
	ft_strcpy(&((*name)[len_str + len_num]), ext);
	free(number);
	return (*name);
}

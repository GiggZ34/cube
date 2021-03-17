/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:01:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/16 22:35:07 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_clear_file(t_file *file, int fd, int code_error)
{
	char	*s;

	while (get_next_line(fd, &s) == 1)
		if (s)
			free(s);
	if (s)
		free(s);
	if (file)
	{
		file->error_code = code_error;
		if (file->map)
			ft_free_array(file->map);
	}
	return (code_error);
}

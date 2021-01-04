/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/02 15:30:54 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char		*ft_search_error(char **str, int id, int row)
{
	char	*tmp;
	char	*s2;

	if ((*str)[id])
		(*str)[id] = 'X';
	else
	{
		tmp = ft_strjoin(*str, "X");
		free(*str);
		*str = tmp;
	}
	s2 = ft_itoa(row + 1);
	tmp = ft_strjoin("line ", s2);
	free(s2);
	s2 = tmp;
	tmp = ft_strjoin(s2, " | ");
	free(s2);
	s2 = tmp;
	tmp = ft_strjoin(s2, *str);
	free(s2);
	free(*str);
	*str = tmp;
	return (*str);
}

static void	ft_init_error_message(t_file *file)
{
	file->error_message[0] = "No error\n\t\t";
	file->error_message[1] = "Crash in the get_next_line function\n\t\t";
	file->error_message[2] = "Your map has invalid characters or is not closed\n\t\t";
	file->error_message[3] = "Crash in allocation memory\n\t\t";
	file->error_message[4] = "Problem with the starting position\n\t\t";
	file->error_message[5] = "An invalid arguments in the description file\n\t\t";
}

int			ft_error_file(t_file *file, int code_error, char *msg)
{
	file->error_code = code_error;
	ft_init_error_message(file);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(file->error_message[file->error_code], 1);
	ft_putstr_fd(msg, 1);
	ft_putchar_fd('\n', 1);
	return (file->error_code);
}

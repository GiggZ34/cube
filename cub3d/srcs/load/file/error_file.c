/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/15 11:39:53 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static char	*ft_init_error_message(int error_code)
{
	char *error_message[12];

	error_message[0] = "No error";
	error_message[1] = "Crash in the get_next_line function : ";
	error_message[2] = "Map has invalid chars or is not closed : ";
	error_message[3] = "Crash in allocation memory : ";
	error_message[4] = "Problem with the starting position : ";
	error_message[5] = "An invalid argument in the file : ";
	error_message[6] = "Problem opening the file";
	error_message[7] = "Wrong extension on source file : ";
	error_message[8] = "Please enter a single argument.";
	error_message[9] = "Unknow extension. : ";
	error_message[10] = "Crash in loading image. : ";
	error_message[11] = "Screen resolution problem.";
	return (error_message[error_code]);
}

int			ft_error_file(t_file *file, int code_error, char *msg)
{
	if (file)
		file->error_code = code_error;
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(ft_init_error_message(code_error), 1);
	ft_putstr_fd(msg, 1);
	ft_putchar_fd('\n', 1);
	return (code_error);
}

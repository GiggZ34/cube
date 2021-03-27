/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:58:06 by grivalan         ###   ########lyon.fr   */
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
	char *error_message[30];

	error_message[succes] = "No error";
	error_message[cash_gnl] = "Crash in the get_next_line function : ";
	error_message[map_not_close] = "Map has invalid chars or is not closed : ";
	error_message[allocation_fail] = "Crash in allocation memory : ";
	error_message[no_player_position] = "Problem with the starting position : ";
	error_message[multiple_player_position] = "Problem with multiple starting position : ";
	error_message[unknow_instruction] = "An invalid argument in the file : ";
	error_message[open_file_fail] = "Problem opening the file";
	error_message[unknow_instruction] = "Wrong extension on source file : ";
	error_message[arguments_error] = "Please enter one or two argument.";
	error_message[unknow_instruction] = "Unknow extension. : ";
	error_message[image_not_exist] = "image not exist. : ";
	error_message[invalid_image] = "Crash in loading image. : ";
	error_message[incorrect_resolution_size] = "Screen resolution problem.";
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

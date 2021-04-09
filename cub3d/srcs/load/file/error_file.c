/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/07 19:57:47 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_search_error(char **str, int id, int row)
{
	char	*tmp;
	char	*tmp2;
	char	*s2;

	if ((*str)[id])
	{
		(*str)[id] = 'X';
		tmp = ft_substr(*str, 0, id);
		tmp2 = ft_substr(*str, id + 1, INT_MAX);
		free(*str);
		*str = ft_strjoin(tmp, "\033[1;31mX\033[0m");
		free(tmp);
		tmp = ft_strjoin(*str, tmp2);
		free(*str);
		*str = tmp;
	}
	else
	{
		tmp = ft_strjoin(*str, "\033[1;31mX\033[0m");
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
	char	*error_message[30];

	error_message[succes] = "\033[32mExit Game!\033[0m";
	error_message[cash_gnl] = "\033[1;31mCrash in the gnl function : \033[0m";
	error_message[map_not_close] = "\033[1;31mMap has invalid chars or is not closed : \033[0m";
	error_message[allocation_fail] = "\033[1;31mCrash in allocation memory : ";
	error_message[no_player_position] = "\033[1;31mProblem with the starting position : \033[0m";
	error_message[multiple_player_position] = "\033[1;31mProblem with multiple starting position : \033[0m";
	error_message[unknow_instruction] = "\033[1;31mAn invalid argument in the file : \033[0m";
	error_message[open_file_fail] = "\033[1;31mProblem opening the file. \033[0m";
	error_message[unknow_instruction] = "\033[1;31mWrong extension on source file : \033[0m";
	error_message[arguments_error] = "\033[1;31mPlease enter one or two argument. \033[0m";
	error_message[unknow_instruction] = "\033[1;31mUnknow extension. : \033[0m";
	error_message[image_not_exist] = "\033[1;31mimage not exist. : \033[0m";
	error_message[invalid_image] = "\033[1;31mCrash in loading image. : \033[0m";
	error_message[incorrect_res] = "\033[1;31mScreen resolution problem. \033[0m";
	error_message[incorrect_res] = "\033[1;31mScreen resolution problem. \033[0m";
	error_message[file_incorrect] = "\033[1;31mFile incorrect\033[0m";
	return (error_message[error_code]);
}

int			ft_error_file(int code_error, char *msg)
{
	if (code_error != succes)
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(ft_init_error_message(code_error), 1);
	ft_putstr_fd(msg, 1);
	ft_putchar_fd('\n', 1);
	return (code_error);
}

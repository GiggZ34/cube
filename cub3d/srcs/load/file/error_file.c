/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 12:18:24 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*generate_line_map_error(char *str, int id)
{
	char	*tmp;
	char	*tmp2;

	if (str[id])
	{
		tmp = ft_substr(str, 0, id);
		tmp2 = ft_substr(str, id + 1, INT_MAX);
		free(str);
		str = ft_strjoin(tmp, "\033[1;31mX\033[0m");
		free(tmp);
		tmp = ft_strjoin(str, tmp2);
		free(str);
		free(tmp2);
		str = tmp;
	}
	else
	{
		tmp = ft_strjoin(str, "\033[1;31mX\033[0m");
		free(str);
		str = tmp;
	}
	return (str);
}

char	*ft_search_error(char **str, int id, int row)
{
	char	*tmp;
	char	*s2;

	*str = generate_line_map_error(*str, id);
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
	char	*msg[30];

	msg[succes] = "\033[32mExit Game!\033[0m";
	msg[cash_gnl] = "\033[1;31mCrash in the gnl function : \033[0m";
	msg[map_not_close] = "\033[1;31mMap is not closed : \033[0m";
	msg[crash_mlx_ft] = "\033[1;31mcrash mlx function : \033[0m";
	msg[allocation_fail] = "\033[1;31mCrash in allocation memory : \033[0m";
	msg[no_s_position] = "\033[1;31mNo starting position\033[0m";
	msg[mult_s_position] = "\033[1;31mMany starting position\033[0m";
	msg[unknow_instruction] = "\033[1;31mAn invalid arg : \033[0m";
	msg[open_file_fail] = "\033[1;31mProblem opening the file. \033[0m";
	msg[wrong_extension] = "\033[1;31mWrong extension file : \033[0m";
	msg[arguments_error] = "\033[1;31mEnter file in argument. \033[0m";
	msg[unknow_instruction] = "\033[1;31mUnknow extension. : \033[0m";
	msg[image_not_exist] = "\033[1;31mimage not exist. : \033[0m";
	msg[invalid_image] = "\033[1;31mCrash in loading image. : \033[0m";
	msg[incorrect_res] = "\033[1;31mScreen resolution problem. \033[0m";
	msg[file_incorrect] = "\033[1;31mFile incorrect\033[0m";
	return (msg[error_code]);
}

int	ft_error_file(int code_error, char *msg)
{
	if (code_error != succes)
		ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(ft_init_error_message(code_error), 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (code_error);
}

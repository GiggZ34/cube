/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:54:46 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 15:15:14 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_lst(t_list *lst, char *type)
{
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (!ft_strncmp(str, type,
				ft_max(ft_strlen(str), ft_strlen(type))))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static int	type_to_lst(t_game *game, char *type)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(type);
	if (!new_lst)
	{
		free(type);
		ft_trash_game(game, allocation_fail, game->file.fd, "type_to_lst");
	}
	if (!game->file.check_file)
		game->file.check_file = new_lst;
	else
	{
		if (check_lst(game->file.check_file, type))
		{
			free(new_lst);
			return (1);
		}
		ft_lstadd_back(&game->file.check_file, new_lst);
	}
	return (0);
}

static char	*type_argument(char *line, char **type)
{
	int		i;

	i = ft_skip_white_space(line);
	if (line[i + 1] != ' ' && line[i + 2] != ' ')
		return (NULL);
	*type = ft_substr(line, i, count_letters(&(line[i])));
	if (!(*type))
		return (NULL);
	return (*type);
}

static int	is_color(char *line)
{
	while (ft_iswhtespace(*line))
		line++;
	while (ft_isalpha(*line))
		line++;
	while (ft_iswhtespace(*line))
		line++;
	return (ft_isdigit(*line));
}

char	**check_format(t_game *game, char *line, char ***array)
{
	char	*type;

	if (!type_argument(line, &type))
		ft_trash_game(game, arguments_error, game->file.fd, "");
	if (type_to_lst(game, type))
		ft_trash_game(game, arguments_error, game->file.fd, "");
	if (!ft_strncmp(type, "R", 2))
		check_res(line, array);
	else if ((!ft_strncmp(type, "F", 2) && is_color(line))
		|| (!ft_strncmp(type, "C", 2) && is_color(line))
		|| !ft_strncmp(type, "L", 2))
		check_color(line, array);
	else
		check_texture(line, array);
	return (*array);
}

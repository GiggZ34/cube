/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:51:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/31 16:34:24 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			check_line(char *line, const char *charset)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(charset, line[i]))
			return (0);
	return (1);
}

static char			**ft_generate_map(t_game *game, t_file *file, char *line)
{
	char	**str;
	int		i;

	if (!check_line(line, "\n 102ESWN"))
	{
		free(line);
		ft_trash_game(game, arguments_error, file->fd, "Invalid line in map or character.");
	}
	if (file->width_map < (int)ft_strlen(line))
		file->width_map = ft_strlen(line);
	if (!(str = ft_calloc(sizeof(char**), ft_count_array(file->map) + 2)))
		return (NULL);
	i = 0;
	if (file->map)
	{
		while (file->map[i])
		{
			str[i] = file->map[i];
			i++;
		}
		free(file->map);
	}
	str[i] = line;
	str[i + 1] = NULL;
	return (str);
}

int				ft_parsing_file(t_game *game, int fd, t_file *file)
{
	char	*line;
	int		rest;

	rest = 1;
	while (rest)
	{
		if ((rest = get_next_line(fd, &line)) == -1)
			return (ft_trash_game(game, cash_gnl, fd, "\n"));
		if (line)
		{
			if (ft_lstsize(file->check_file) < ARG_FILE && line[0])
			{
				ft_file_to_struct(game, line, fd);
				free(line);
			}
			else if (ft_lstsize(file->check_file) == ARG_FILE && (file->map || line[0]))
			{
				if (!(file->map = ft_generate_map(game, file, line)))
					return (ft_trash_game(game, allocation_fail, fd, "\n"));
			}
			else
				free(line);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:51:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/08 15:35:54 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line(char *line, const char *charset)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(charset, line[i]))
			return (0);
	return (1);
}

static char	**ft_generate_map(t_game *game, t_file *file, char *line)
{
	char	**str;
	int		i;

	if (!check_line(line, "\n 102ESWNL"))
	{
		free(line);
		ft_trash_game(game, arguments_error, file->fd, "Invalid map.");
	}
	if (file->width_map < (int)ft_strlen(line))
		file->width_map = ft_strlen(line);
	str = ft_calloc(sizeof(char **), ft_count_array(file->map) + 2);
	if (!str)
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
	return (str);
}

static int	is_line_map(char *line)
{
	int	i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i++] != '1')
			return (0);
	}
	return (1);
}

static void	tidy_arguments(t_game *game, char *line, int fd, int *map)
{
	if (!(*map))
		(*map) = is_line_map(line);
	if (!(*map) && line[0])
	{
		ft_file_to_struct(game, line, fd);
		free(line);
	}
	else if (*map && (game->file.map || line[0]))
	{
		game->file.map = ft_generate_map(game, &game->file, line);
		if (!game->file.map)
			ft_trash_game(game, allocation_fail, fd, "\n");
	}
	else
		free(line);
}

int	ft_parsing_file(t_game *game, int fd)
{
	char	*line;
	int		rest;
	int		map;

	map = 0;
	rest = 1;
	while (rest)
	{
		rest = get_next_line(fd, &line);
		if (rest == -1)
			return (ft_trash_game(game, cash_gnl, fd, "\n"));
		if (line)
			tidy_arguments(game, line, fd, &map);
	}
	if (!game->file.map)
		ft_trash_game(game, map_not_close, -1, "no Map");
	return (0);
}

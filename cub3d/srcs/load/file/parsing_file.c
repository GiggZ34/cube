/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:51:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 17:07:36 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_check_file(t_game *game, t_file *file)
{
	t_screen	screen;

	screen = game->screen;
	if (screen.width > -1 && screen.height > -1
			&& file->ground_color > -1 && file->sky_color > -1
			&& file->texture_ea && file->texture_no && file->texture_ea
			&& file->texture_we && file->texture_s)
		return (1);
	return (0);
}

static char			**ft_generate_map(t_file *file, char *line)
{
	char	**str;
	int		i;

	if (!line)
		return (NULL);
	if (file->width_map < (int)ft_strlen(line))
		file->width_map = ft_strlen(line);
	if (!(str = calloc(sizeof(char **), ft_count_array(file->map) + 2)))
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
			return (ft_trash_game(game, cash_gnl, fd));
		if (line)
		{
			if (!ft_check_file(game, file) && line[0])
			{
				ft_file_to_struct(game, line, fd);
				free(line);
			}
			else if (ft_check_file(game, file) && (file->map || line[0]))
			{
				if (!(file->map = ft_generate_map(file, line)))
					return (ft_trash_game(game, allocation_fail, fd));
			}
			else
				free(line);
		}
	}
	return (0);
}

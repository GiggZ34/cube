/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:51:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/01 12:31:02 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_check_file(t_game *game)
{
	t_file		*file;
	t_screen	screen;

	file = game->file;
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
		return (file->map);
	if (file->width_map < (int)ft_strlen(line))
		file->width_map = ft_strlen(line);
	if (!(str = calloc(sizeof(char **), ft_count_array(file->map) + 2)))
		return (0);
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
	str[i + 1] = 0;
	return (str);
}

int				ft_parsing_file(t_game *game, int fd, t_file *file)
{
	char	*line;
	int		rest;

	rest = 1;
	while (file->error_code == 0 && rest == 1)
	{
		if ((rest = get_next_line(fd, &line)) == -1)
			ft_error_file(file, 1, "in function ft_parsing_file");
		if (file->error_code == 0 && line)
		{
			if (!ft_check_file(game) && line[0])
			{
				ft_file_to_struct(game, file, line);
				free(line);
			}
			else if (ft_check_file(game) && (file->map || line[0]))
			{
				if (!(file->map = ft_generate_map(file, line)))
					ft_error_file(file, 3, "in function ft_parsing_file");
			}
			else
				free(line);
		}
	}
	return (file->error_code);
}

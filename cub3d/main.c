/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:41:36 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/02 15:33:32 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	regex_file(const char *s)
{
	size_t len;

	if ((len = ft_strlen(s)) > 4 && s[len - 4] == '.' && s[len - 3] == 'c'
				&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (1);
	return (0);
}

static t_file	*ft_init_file()
{
	t_file *file;

	if (!(file = ft_calloc(sizeof(t_file), 1)))
		return (0);
	file->resolution = '\0';
	file->north_texture = 0;
	file->south_texture = 0;
	file->west_texture = 0;
	file->east_texture = 0;
	file->ground = '\0';
	file->sky = '\0';
	file->error_code = 0;
	file->map = 0;
	return (file);
}

static int	ft_clear_file(t_file *file, int fd, int error_code)
{
	char	*s;
	int		i;

	s = 0;
	while (get_next_line(fd, &s) == 1)
		if (s)
			free(s);
	if (s)
		free(s);
	if (file->north_texture)
		free(file->north_texture);
	if (file->south_texture)
		free(file->south_texture);
	if (file->west_texture)
		free(file->west_texture);
	if (file->east_texture)
		free(file->east_texture);
	if (file->sprite_texture)
		free(file->sprite_texture);
	ft_free_array(file->map);
	if (file)
		free(file);
	return (error_code);
}

int			main(int ac, char **av)
{
	t_file	*file;
	int		fd;
	int		error_code;
	int		i;

	if (ac == 2)
	{
		if (!(file = ft_init_file()))
			return (-3);
		if (!regex_file(av[1]))
			return (ft_clear_file(file, fd, -1));
		if ((fd = open(av[1], O_RDONLY)) == -1)
			return (ft_clear_file(file, fd, -2));
		if (ft_parsing_file(fd, file) != 0)
			return (ft_clear_file(file, fd, file->error_code));
		if (ft_check_map(file) != 0)
			return (ft_clear_file(file, fd, file->error_code));
		dprintf(1, "%c  | %d %d\n", file->resolution, file->resolution_x, file->resolution_y);
		dprintf(1, "NO | %s\n", file->north_texture);
		dprintf(1, "SO | %s\n", file->south_texture);
		dprintf(1, "WE | %s\n", file->west_texture);
		dprintf(1, "EA | %s\n", file->east_texture);
		dprintf(1, "%c  | %d %d %d\n", file->ground, file->ground_color[0], file->ground_color[1], file->ground_color[2]);
		dprintf(1, "%c  | %d %d %d\n", file->sky, file->sky_color[0], file->sky_color[1], file->sky_color[2]);
		i = -1;
		while (file->map[++i])
			dprintf(1, "%s\n", file->map[i]);
		dprintf(1, "error_code : %d\n", file->error_code);
		ft_clear_file(file, fd, error_code);
		close(fd);
	}
	return (0);
}

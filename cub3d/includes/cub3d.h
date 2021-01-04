/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:56:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/02 14:37:18 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <mlx.h>

typedef struct		s_file
{
	char			resolution;
	unsigned short	resolution_x;
	unsigned short	resolution_y;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*sprite_texture;
	char			ground;
	unsigned char	ground_color[3];
	char			sky;
	unsigned char	sky_color[3];
	char			**map;
	int				error_code;
	char			*error_message[6];
}					t_file;

/*
** Function free
*/

void	ft_free_array(char **array);

/*
** Function parsing file
*/

int		ft_parsing_file(int fd, t_file *file);
char	**ft_generate_map(char **map, char *line);
int		ft_file_to_struct(t_file *file, char *line);
int		ft_check_map(t_file *file);
int		ft_modif_map(t_file *file, char **map_checked);

/*
** Function error
*/

int		ft_error_file(t_file *file, int code_error, char *msg);
char	*ft_search_error(char **str, int id, int row);

#endif

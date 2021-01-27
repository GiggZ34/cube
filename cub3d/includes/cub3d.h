/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:56:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 17:23:20 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>
# include "../mlx/mlx.h"
# define FAIL_EXIT -1
# define MIN_SCREEN_WIDTH 100
# define MIN_SCREEN_HEIGHT 100
# define MAX_SCREEN_WIDTH 2560
# define MAX_SCREEN_HEIGHT 1400
# define FOV 60.0

typedef struct		s_wall
{
	int				id;
	double			a;
	double			b;
	double			c;
	double			d;
	t_dot			pos;
	double			width;
	double			height;
	void			*add;
}					t_wall;

typedef struct		s_texture
{
	char			*type;
	int				**color;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct		s_file
{
	int				ground_color;
	int				sky_color;
	char			**map;
	int				error_code;
	char			*error_message[8];
	t_texture		*texture_no;
	t_texture		*texture_so;
	t_texture		*texture_we;
	t_texture		*texture_ea;
	t_texture		*texture_s;
}					t_file;

typedef struct		s_screen
{
	int				width;
	int				height;
	double			w_vec;
	double			h_vec;
	double			height_fov;
	t_dot			first_pixel;
	int				first_pixel_x;
	int				first_pixel_y;
}					t_screen;

typedef struct		s_player
{
	t_dot			position;
	t_vector		view;
	char			dir;
	double			vx;
	double			vy;
	double			angle;
	int				live;
	t_texture		*tile_sheet;
}					t_player;

typedef struct		s_sprite
{
	char			*type;
	t_dot			position;
	double			vx;
	double			vy;
	double			angle;
	int				live;
	int				state;
	t_texture		*tile_sheet;
}					t_sprite;

typedef struct		s_game
{
	void			*mlx;
	void			*window;
	t_file			*file;
	t_screen		*screen;
	t_player		*player;
	t_list			*lst_sprites;
	t_list			*lst_planes;
	t_list			*lst_walls;
}					t_game;

/*
**	Functions tools
*/

int					ft_color_generate(int red, int green, int blue, int alpha);

/*
**	Functions free
*/

void				ft_free_array(char **array);
int					ft_clear_file(t_file *file, int fd, int error_code);

/*
**	Functions load
*/

int					ft_load(char *r_f, t_game *game);
int					ft_init_file(t_file *file, t_game *game, char *dir_file);
int					ft_parsing_file(t_game *game, int fd, t_file *file);
char				**ft_generate_map(char **map, char *line);
int					ft_file_to_struct(t_game *game, t_file *file, char *line);
int					ft_check_map(t_game *game, t_file *file);
void				ft_scan_map(t_game *game, char **map, int i, int j);
int					ft_create_plane(t_game *game, int x, int y, char dir);
int					ft_modif_map(t_game *game, char **map_checked);
int					ft_create_walls(t_list *lst_planes, t_game *game);
int					ft_delete_walls(t_list **lst_walls);
int					ft_img_generate(void *mlx, t_file *file, char *dir, char *type);
void				ft_screen(t_game *game);
int					ft_init_ennemy(t_game *game, int x, int y);
t_player			*ft_init_player(t_game *game, int x, int y, char dir);
int					ft_check_struct(t_game *game);

/*
**	Functions error
*/

int					ft_error_file(t_file *file, int code_error, char *msg);
char				*ft_search_error(char **str, int id, int row);

/*
**	Functions mini-map
*/

int					ft_mini_map(t_game *game);

/*
**	Functions draw
*/

int					ft_draw(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:56:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/09 17:41:06 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef LINUX
#  include "../mlx/mlx.h"
#  include "control_mac.h"
# else
#  include <mlx.h>
#  include "control_linux.h"
# endif
# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <math.h>
# define FAIL_EXIT -1
# define MIN_SCREEN_WIDTH 100
# define MIN_SCREEN_HEIGHT 100
# define MAX_SCREEN_WIDTH 2560
# define MAX_SCREEN_HEIGHT 1400
# define NB_THREADS 1
# define FRAME_RATE 50000
# define DIST_COLLIDE 1.0
# define ROTATE_SPEED M_PI
# define SPEED_MAX 2
# define MOUSE_SENS 2
# define FOV 60.0
# define FOV_COS -0.30
# define FOV_DIST 50
# define FOV_DIST_SQRT 5

typedef struct		s_texture
{
	char			*type;
	int				*color;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct		s_view
{
	t_vector		view;
	t_list			*lst_sprites;
	t_vector		*vector;
	t_dot			extremity[2];
	t_vector		*tab_vectors;
	t_list			*sprites_in_fov;
}					t_view;

typedef struct		s_collide
{
	t_vector		top;
	t_vector		bottom;
	t_vector		left;
	t_vector		right;
	int				top_bool;
	int				bottom_bool;
	int				left_bool;
	int				right_bool;
}					t_collide;

typedef struct		s_tab_plane
{
	t_list			**left;
	t_list			**right;
	t_list			**top;
	t_list			**bottom;
}					t_tab_plane;

typedef struct		s_file
{
	int				ground_color;
	int				sky_color;
	char			**map;
	int				width_map;
	int				height_map;
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
	void			*ptr;
	int				*color;
	int				size;
	int				endian;
	int				bit;
}					t_screen;

typedef struct		s_control
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				up;
	int				down;
	int				right;
	int				left;
	int				run;
	int				mouse_x_tmp;
	int				mouse_y_tmp;
	int				mouse_x;
	int				mouse_y;
}					t_control;

typedef struct		s_player
{
	t_dot			position;
	t_view			view;
	t_collide		collide;
	t_control		control;
	double			walk_volocity;
	double			walk_speed_max;
	double			run_volocity;
	double			run_speed_max;
	double			vx;
	double			vy;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	int				live;
	t_texture		*tile_sheet;
}					t_player;

typedef struct		s_sprite
{
	t_dot			position;
	t_plane			plane;
	t_vector		normal;
	t_dot			frist_px;
	t_vector		vec_write;
	t_vector		first_col;
	t_collide		collide;
	double			vx;
	double			vy;
	double			width;
	double			height;
	double			ratio;
	double			angle;
	int				live;
	int				state;
	t_texture		*tile_sheet;
}					t_sprite;

typedef	struct		s_dt
{
	struct timeval	time;
	unsigned long	time_start;
	unsigned long	time_end;
	double			dt;
	char			*dt_str;
}					t_dt;


typedef struct		s_game
{
	void			*mlx;
	void			*window;
	t_dt			dt;
	pthread_t		*thread[NB_THREADS];
	t_file			*file;
	t_screen		screen;
	t_player		*player;
	t_list			*lst_sprites;
	t_tab_plane		tab_planes;
	t_list			*lst_planes_top;
	t_list			*lst_planes_bottom;
	t_list			*lst_planes_right;
	t_list			*lst_planes_left;
}					t_game;

/*
**	Functions tools
*/

int					ft_color_generate(int red, int green, int blue, int alpha);
void				ft_delta_time_generate(t_game *game);

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
int					ft_file_to_struct(t_game *game, t_file *file, char *line);
char				**ft_map_cpy(char **map, int height);
int					ft_check_map(t_game *game, t_file *file);
void				ft_scan_map(t_game *game, char **map, int i, int j);
int					ft_create_plane(t_game *game, t_list **lst, int *pos, char dir);
t_plane				*ft_search_plane(t_list *lst, int x, int y, char dir);
void				ft_sort_planes(t_list *lst);
void				ft_asort_planes(t_list *lst);
int					ft_lst_planes_to_tab(t_game *game);
int					ft_img_generate(void *mlx, t_file *file, char *dir, char *type);
int					ft_screen(t_game *game);
int					ft_init_tab_vector(t_game *game, t_dot origin);
int					ft_init_ennemy(t_game *game, int x, int y);
t_player			*ft_init_player(t_game *game, int x, int y, char dir);
int					ft_check_struct(t_game *game);

/*
**	Function update
*/

int					ft_game_loop(t_game *game);
int					ft_rotate_vectors_collides(t_player *player, double angle);
int					ft_translation_vector(t_game *game, double velocity, double angle);
int					ft_edit_sprite_plane(t_sprite *sprite, t_vector player_normal);

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

void				*ft_draw(void *g);
int					ft_pixel_color(t_game *game, t_vector v);
int					ft_print_fps(t_game *game, char *fps);

#endif

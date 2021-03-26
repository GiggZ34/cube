/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:56:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/25 16:08:33 by grivalan         ###   ########lyon.fr   */
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
# define NB_THREADS 4
# define UNVISIBLE_COLOR -16777216
# define NB_IMG_ANIM_GUNS 7
# define NB_ANIM_GUNS 3
# define FPS_MAX 80
# define FPS_MIN 50
# define FRAME_RATE 50000
# define DIST_COLLIDE 1.0
# define ROTATE_SPEED_X M_PI / 4
# define ROTATE_SPEED_Z M_PI / 4
# define SPEED_MAX 10
# define FOV 60.0
# define FOV_COS -0.75
# define FOV_DIST 50
# define FOV_DIST_SQRT 5

typedef enum		e_error_code
{
	succes,
	mlx_creation_fail,
	win_creation_fail,
	load_texture_fail,
	color_generation_fail,
	crash_mlx_function,
	open_file_fail,
	cash_gnl,
	image_not_exist,
	invalid_image,
	unknow_instruction,
	incorrect_color_code,
	incorrect_resolution_size,
	allocation_fail,
	no_player_position,
	multiple_player_position,
	put_image_fail

}					t_error_code;

typedef enum		e_arms
{
	barel_fusil = 6,
	damages_fusil = 20
}					t_arms;

typedef enum		e_states
{
	rest,
	reload,
	shoot,
	escape,
	search
}					t_states;

typedef enum		e_player_anim
{
	anim_rest = 1,
	anim_reload = 7,
	anim_shoot = 2
}					t_player_anim;

typedef enum		e_data_sprite
{
	time_search = 10
}					t_data_sprite;

typedef struct		s_color
{
	double			size;
	int				color;
	char			collide;
}					t_color;


typedef struct		s_save_img
{
	char			*flag;
	char			*file_size;
	char			*first_px;
	char			*size;
	char			*width;
	char			*height;
	char			*planes;
	char			*bit_count;
	char			*compression;
	char			*size_image;
	char			*x_pels_per_meter;
	char			*y_pels_per_meter;
	char			*clr_used;
	char			*clr_important;

}					t_save_img;


typedef struct		s_texture
{
	void			*ptr;
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
	int				scale;
	void			*ptr;
	int				*color;
	int				size;
	int				endian;
	int				bit;
	int				*color_objs;
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
	int				squat;
	int				mouse_x_tmp;
	int				mouse_y_tmp;
	int				mouse_x;
	int				mouse_y;
	int				shoot;
	int				reload;
}					t_control;

typedef struct		s_obj
{
	t_texture		obj_texture;
	int				width;
	int				height;
	double			ratio_pos;
	double			ratio_size;
	t_dot			position;
}					t_obj;

typedef struct		s_player
{
	int				state;
	double			anim_frame;
	int				ammunition;
	t_screen		*arm;
	t_dot			position;
	t_view			view;
	t_collide		collide;
	t_control		control;
	t_screen		*gun[NB_ANIM_GUNS];
	double			dist_screen;
	double			walk_speed;
	double			trans_speed;
	double			walk_speed_max;
	double			run_speed_max;
	double			dir_walk;
	double			dir_trans;
	double			vx;
	double			vy;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	int				live;
	t_obj			guns;
}					t_player;

typedef struct		s_sprite
{
	t_dot			position;
	t_plane			plane;
	t_vector		normal;
	t_dot			frist_px;
	t_vector		vec_write;
	t_vector		sprite_to_player;
	double			dist_to_player;
	t_vector		first_col;
	t_collide		collide;
	double			vx;
	double			vy;
	double			width;
	double			height;
	double			ratio;
	double			angle;
	double			time_search;
	int				live;
	t_states		state;
	t_texture		*tile_sheet;
}					t_sprite;

typedef	struct		s_dt
{
	struct timeval	time;
	unsigned long	time_start;
	unsigned long	time_end;
	double			dt;
	char			*dt_str;
	char			*scale_str;
}					t_dt;

typedef struct		s_sky_ground
{
	t_plane			ground_plane;
	t_texture		ground_texture;
	t_plane			sky_plane;
	t_texture		sky_texture;

}					t_sky_ground;

typedef struct		s_game
{
	void			*mlx;
	void			*window;
	t_dt			dt;
	t_file			file;
	t_screen		screen;
	t_player		player;
	t_list			*lst_sprites;
	t_tab_plane		tab_planes;
	t_list			*lst_planes_top;
	t_list			*lst_planes_bottom;
	t_list			*lst_planes_right;
	t_list			*lst_planes_left;
	t_sky_ground	sky_ground;
}					t_game;

typedef struct		s_thread
{
	int				id;
	t_game			*game;
	int				start;
	int				size;
	pthread_t		thread;
	t_screen		*screen;
}					t_thread;

/*
**	Functions tools
*/

int					ft_color_generate(int red, int green, int blue, int alpha);
void				ft_delta_time_generate(t_game *game);
t_player_anim		ft_define_nb_anim(int state);

/*
**	Functions free
*/

void				ft_free_array(char **array);
int					ft_clear_file(t_file *file, int fd, int error_code);
int					ft_trash_game(t_game *game, t_error_code code, int fd);

/*
**	Functions load
*/

int					ft_load(char *r_f, t_game *game);
int					ft_init_file(t_file *file, t_game *game, char *dir_file);
int					ft_parsing_file(t_game *game, int fd, t_file *file);
int					ft_file_to_struct(t_game *game, char *line, int fd);
char				**ft_map_cpy(char **map, int height);
int					ft_check_map(t_game *game, t_file *file);
void				ft_scan_map(t_game *game, char **map, int i, int j);
int					ft_create_plane(t_game *game, t_list **lst, int *pos, char dir);
t_plane				*ft_search_plane(t_list *lst, int x, int y, char dir);
void				ft_sort_planes(t_list *lst);
void				ft_asort_planes(t_list *lst);
int					ft_lst_planes_to_tab(t_game *game);
int					ft_img_generate(t_game *game, char *dir, char *type);
int					ft_screen(t_game *game);
int					ft_init_screen(t_game *game, t_screen *img, int nb_img, int state);
int					ft_init_tab_vector(t_game *game, t_dot origin);
int					ft_init_ennemy(t_game *game, int x, int y);
int					ft_init_player(t_game *game, int x, int y, char dir);
int					ft_load_tilesheet_obj(t_game *game, char *path);

/*
**	Function update
*/

int					ft_game_loop(t_game *game);
int					ft_rotate_vectors_collides(t_player *player, double angle);
int					ft_translation_vector(t_game *game, double v, double *speed, double angle);
int					ft_edit_sprite_plane(t_sprite *sprite, t_vector player_normal);
int					ft_update_sprites(/*t_game *game, */t_list *lst_sprites, t_player *player);
void				ft_sort_lst_sprite(t_list **begin);
int					ft_update_player(t_game *game, t_player *player);
void				ft_move_player(t_game *game, t_player *player);
void				ft_rotate_player(t_game *game, t_player *player, double x, double y);

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

int					ft_image_save(t_game *game);
void				ft_draw_multi_threads(t_game *game, t_screen *gun);
int					ft_pixel_color(t_game *game, t_vector v, t_sprite *s);
int					ft_print_fps(t_game *game, char *fps, char *scale);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 11:56:01 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 17:07:38 by grivalan         ###   ########lyon.fr   */
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
# include <signal.h>
# define PRECISION .00001
# define NB_THREADS 8
# define INVISIBLE_COLOR -16777216
# define SCALE_MAX 4
# define FPS_MAX 60
# define FPS_MIN 8
# define DIST_MAX 0.3
# define ROTATE_SPEED 0.785
# define WEIGHTLESSNESS 9.81
# define SPEED_MAX 10
# define FOV 80.0
# define FOV_COS -0.1
# define FOV_DIST 50
# define FOV_DIST_SQRT 5
# define SOUND_TIME 60

typedef enum e_error_code
{
	succes,
	mlx_creation_fail,
	win_creation_fail,
	load_texture_fail,
	color_generation_fail,
	crash_mlx_ft,
	open_file_fail,
	cash_gnl,
	image_not_exist,
	invalid_image,
	unknow_instruction,
	wrong_extension,
	incorrect_color_code,
	incorrect_res,
	allocation_fail,
	no_s_position,
	mult_s_position,
	put_image_fail,
	arguments_error,
	map_not_close,
	fail_destroy_image,
	lack_of_arguments,
	file_incorrect
}t_error_code;

typedef enum e_fusil
{
	nb_img_anim = 7,
	nb_anim = 3,
	barel_fusil = 6,
	damages_fusil = 20
}t_fusil;

typedef enum e_states
{
	rest,
	reload,
	shoot,
	escape,
	search
}t_states;

typedef enum e_player_anim
{
	anim_rest = 1,
	anim_reload = 7,
	anim_shoot = 2
}t_player_anim;

typedef enum e_data_sprite
{
	time_search = 10
}t_data_sprite;

typedef struct s_color
{
	double		size;
	int			color;
	t_dot		inter;
}t_color;

typedef struct s_texture
{
	void				*ptr;
	char				*type;
	int					*color;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	struct s_texture	*next;
}t_texture;

typedef struct s_view
{
	t_vector	view;
	t_vector	*vector;
	t_dot		extremity[2];
	t_vector	*tab_vectors;
	t_list		*sprites_in_fov;
}t_view;

typedef struct s_collide
{
	t_vector	top;
	t_vector	bottom;
	t_vector	left;
	t_vector	right;
	int			top_bool;
	int			bottom_bool;
	int			left_bool;
	int			right_bool;
}t_collide;

typedef struct s_tab_plane
{
	t_list		**left;
	t_list		**right;
	t_list		**top;
	t_list		**bottom;
}t_tab_plane;

typedef struct s_file
{
	int			fd;
	int			nb_img;
	t_list		*check_file;
	int			ground_color;
	int			sky_color;
	float		light_color[3];
	char		**map;
	int			width_map;
	int			height_map;
	int			error_code;
	char		*error_message[8];
	t_texture	*texture_no;
	t_texture	*texture_so;
	t_texture	*texture_we;
	t_texture	*texture_ea;
	t_texture	*texture_s;
	t_texture	*texture_c;
	t_texture	*texture_f;
	t_texture	*texture_light;
	t_texture	*texture_obj;
}t_file;

typedef struct s_screen
{
	int			width;
	int			height;
	double		w_vec;
	double		h_vec;
	int			scale;
	void		*ptr;
	int			*color;
	int			size;
	int			endian;
	int			bit;
	int			*color_objs;
	int			max_x;
	int			max_y;
}t_screen;

typedef struct s_control
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			up;
	int			down;
	int			right;
	int			left;
	int			run;
	int			squat;
	int			jump;
	int			mouse_x_pos;
	int			mouse_y_pos;
	int			mouse_x;
	int			mouse_y;
	int			mouse_diff_x;
	int			mouse_diff_y;
	int			shoot;
	int			reload;
}t_control;

typedef struct s_obj
{
	t_texture	obj_texture;
	int			width;
	int			height;
	double		ratio_pos;
	double		ratio_size;
	t_dot		position;
}t_obj;

typedef struct s_light
{
	char			type;
	float			x;
	float			y;
	float			z;
	unsigned char	rgb[3];
	t_texture		*t;
	float			width;
	float			height;
	float			ratio;
	t_plane			plane;
	struct s_light	*next;
}t_light;

typedef struct s_player
{
	int			state;
	double		anim_frame;
	int			ammunition;
	t_screen	*arm;
	t_dot		position;
	t_view		view;
	t_collide	collide;
	t_control	control;
	t_screen	**gun;
	double		dist_screen;
	double		walk_speed;
	double		trans_speed;
	double		walk_speed_max;
	double		run_speed_max;
	double		dir_walk;
	double		dir_trans;
	double		pos_z_min;
	double		vx;
	double		vy;
	double		vz;
	double		angle_x;
	double		angle_z;
	int			live;
	t_obj		guns;
}t_player;

typedef struct s_sprite
{
	t_dot		position;
	t_plane		plane;
	t_vector	normal;
	t_dot		frist_px;
	t_vector	vec_write;
	t_vector	sprite_to_player;
	double		dist_to_player;
	t_vector	first_col;
	t_collide	collide;
	double		vx;
	double		vy;
	double		width;
	double		height;
	double		ratio;
	double		angle;
	double		time_search;
	int			live;
	t_states	state;
	t_texture	*tile_sheet;
}t_sprite;

typedef struct s_dt
{
	struct timeval	time;
	unsigned long	time_start;
	unsigned long	time_end;
	double			dt;
	char			*dt_str;
	char			*scale_str;
}t_dt;

typedef struct s_sky_ground
{
	t_plane		ground_plane;
	t_plane		sky_plane;
}t_sky_ground;

typedef struct s_system_call
{
	pthread_t	thread;
	const char	*cmd;
	int			loop;
}t_system_call;

typedef struct s_music
{
	int			time;
	int			play;
}t_music;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	int				debug;
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
	t_music			music;
	int				save_picture;
	int				exit;
	t_light			*light;
}t_game;

typedef struct s_thread
{
	int			id;
	t_game		*game;
	int			start;
	int			size;
	t_sprite	*sprite;
	pthread_t	thread;
	t_screen	*screen;
}t_thread;

/*
**	Functions tools
*/

int				ft_color_generate(int red, int green, int blue, int alpha);
void			ft_delta_time_generate(t_game *game);
t_player_anim	ft_define_nb_anim(int state);
int				ft_change_resolution(t_game *game, int fd);
int				count_letters(char *line);

/*
**	Functions free
*/

void			ft_free_array(char **array);
int				ft_trash_game(t_game *g, t_error_code cd, int fd, char *mg);
void			clear_light(t_game *game);
void			*free_with_protect(void *content);
void			delete(void *content);
int				ft_free_hud(t_game *g, t_player *p);
void			*free_texture(t_game *game, t_texture *texture);

/*
**	Functions load
*/

int				ft_load(char *r_f, t_game *game);
int				ft_init_file(t_file *file, t_game *game, char *dir_file);
int				ft_parsing_file(t_game *game, int fd);
void			init_color_light(t_game *game, float r, float g, float b);
void			ft_init_light(t_game *game, int x, int y);
int				ft_file_to_struct(t_game *game, char *line, int fd);
char			**check_format(t_game *game, char *line, char ***array);
char			**check_color(char *line, char ***array);
char			**check_res(char *line, char ***array);
char			**check_texture(char *line, char ***array);
char			**ft_map_cpy(char **map, int height);
int				ft_check_map(t_game *game, t_file *file);
void			ft_scan_map(t_game *game, char **map, int i, int j);
int				ft_create_plane(t_game *game, t_list **lst, int *pos, char dir);
t_plane			*ft_search_plane(t_list *lst, int x, int y, char dir);
void			ft_sort_planes(t_list *lst);
void			ft_asort_planes(t_list *lst);
int				ft_lst_planes_to_tab(t_game *game);
int				ft_img_generate(t_game *game, char *dir, char *type);
int				ft_screen(t_game *game);
int				ft_init_screen(t_game *g, t_screen *img, int nb_img, int state);
int				ft_init_tab_vector(t_game *game, t_dot origin);
int				ft_init_ennemy(t_game *game, int x, int y);
int				ft_init_player(t_game *game, int x, int y, char dir);
int				ft_load_tilesheet_obj(t_game *game, char *path);

/*
**	Function update
*/

int				ft_game_loop(t_game *game);
void			playmusic(t_game *game);
void			play_sound(const char *cmd_line);
int				ft_rotate_vectors_collides(t_player *player, double angle);
int				ft_translation_vector(t_game *g, double v, double *s, double a);
int				ft_edit_sprite_plane(t_sprite *sprite, t_vector player_normal);
int				ft_update_sprites(t_list *lst_sprites, t_player *p);
void			ft_sort_lst_sprite(t_list **begin);
int				ft_update_player(t_game *game, t_player *player);
void			player_shoot(t_game *game, t_player *player);
int				mouse_move(int x, int y, t_game *game);
int				ft_mouse_press(int button, int x, int y, t_game *game);
void			ft_move_player(t_game *game, t_player *player);
void			ft_rotate_player(t_game *g, t_player *p, double x, double y);
void			ft_update_planes(t_game *game);

/*
**	Functions error
*/

int				ft_error_file(int code_error, char *msg);
char			*ft_search_error(char **str, int id, int row);

/*
**	Functions mini-map
*/

int				ft_mini_map(t_game *game);

/*
**	Functions draw
*/

size_t			ft_image_save(t_game *game);
void			ft_draw_multi_threads(t_game *game, t_screen *gun);
int				ft_pixel_color(t_game *game, t_vector *v, t_sprite *s);
int				define_lst_planes(t_game *g, t_vector *v, t_list ***t, char d);
t_list			*search_list(t_list **lst, int pos, int step, int max);
int				search_color_x(t_game *g, t_vector *vec, t_color *x);
int				search_color_y(t_game *g, t_vector *vec, t_color *y, t_color x);
int				ft_is_in_wall(t_texture *texture, t_dot inter, char dir);
double			ft_is_wall(t_game *g, t_plane *plane, t_vector *v, t_dot *dot);
int				ft_search_sprite(t_game *g, t_vector *v, t_color *s, t_list *l);
int				ft_print_fps(t_game *game, char *fps, char *scale);
int				luminosity_px(t_game *game, int color, t_dot collide);
void			check_light(t_game *game, t_dot collide, float *rgb);

#endif

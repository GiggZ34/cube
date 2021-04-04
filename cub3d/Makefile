# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 18:59:35 by grivalan          #+#    #+#              #
#    Updated: 2021/04/04 19:05:09 by grivalan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

ERASE		=	\033[2K\r
GREY		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
PINK		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
BOLD		=	\033[1m
UNDER		=	\033[4m
SUR			=	\033[7m
END			=	\033[0m

UNAME := $(shell uname)

NAME =		cub3d

NAME2	=	cub3dlinux

LIB  =		./libft

MLX  =		./mlx

SRCS =		main.c\
			srcs/load/ft_load.c\
			srcs/load/file/ft_init_file.c\
			srcs/load/file/parsing_file.c\
			srcs/load/file/ft_file_to_struct.c\
			srcs/load/file/error_file.c\
			srcs/load/file/check_format.c\
			srcs/load/file/check_color.c\
			srcs/load/file/check_res.c\
			srcs/load/file/check_texture.c\
			srcs/load/map/check_map.c\
			srcs/load/map/ft_map_cpy.c\
			srcs/load/map/ft_scan_map.c\
			srcs/load/map/ft_create_plane.c\
			srcs/load/planes/ft_search_plane.c\
			srcs/load/planes/ft_sort_planes.c\
			srcs/load/planes/ft_lst_planes_to_tab.c\
			srcs/load/file/ft_image_generate.c\
			srcs/load/screen/ft_screen.c\
			srcs/load/objects/load_objects.c\
			srcs/view/ft_init_tab_vector.c\
			srcs/sprite/ft_rotate_vectors_collides.c\
			srcs/view/ft_translation_vector.c\
			srcs/sprite/init_player.c\
			srcs/sprite/init_ennemy.c\
			srcs/sprite/ft_edit_sprite_plan.c\
			srcs/clear/clear_file.c\
			srcs/tools/ft_color_generate.c\
			srcs/tools/ft_delta_time_generator.c\
			srcs/tools/ft_define_nb_anim.c\
			srcs/tools/del.c\
			srcs/tools/change_resolution.c\
			srcs/tools/count_letters.c\
			srcs/update/ft_update.c\
			srcs/update/ft_update_sprites.c\
			srcs/update/ft_update_player.c\
			srcs/update/ft_rotate_player.c\
			srcs/update/ft_move_player.c\
			srcs/update/ft_update_planes.c\
			srcs/draw/ft_draw.c\
			srcs/draw/ft_pixel_color.c\
			srcs/draw/ft_print_fps.c\
			srcs/image_save/image_save.c\
			srcs/sound/play_sound.c\

CC = gcc

ifeq ($(UNAME), Linux)
CFLAGS =	-Wall -Wextra -Werror -Ofast -D LINUX
else
CFLAGS =	-Wall -Wextra -Werror -Ofast -flto -march=native -ffast-math
endif

INCLUDES =	includes

OBJS =		$(SRCS:.c=.o)

%.o: %.c includes/cub3d.h libft/libft.h includes/control_mac.h includes/control_linux.h
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDES)
			@printf "$(ERASE)$(YELLOW)$<$(END)"

$(NAME):	$(OBJS)
		@printf "$(ERASE)";
		@$(MAKE) -C $(LIB)
		@$(MAKE) -C $(MLX)
		@cp mlx/libmlx.dylib .
		@$(CC) -o $(NAME) $(OBJS) -I $(INCLUDES) libft/libft.a -Lmlx -lmlx -lm
		@printf "$(ERASE)$(GREEN)CUB3D\t\t->\t\tCOMPILED$(END)\n"

$(NAME2) :	$(OBJS)
		@$(MAKE) -C $(LIB)
		@$(CC) -o $(NAME) $(OBJS) -I $(INCLUDES) libft/libft.a -lmlx -lm -lbsd -lX11 -lXext -lpthread
		@printf "$(ERASE)$(GREEN)CUB3D\t\t->\t\tCOMPILED$(END)\n"

all :		$(NAME)

linux :		$(NAME2)

imgclean :
		@rm -f *.bmp
			@printf "$(ERASE)$(RED)IMAGES\t\t->\t\tDESTROY$(END)\n"

clean :
		@rm -rf $(OBJS)
		@printf "$(ERASE)$(RED)CUB3D\t\t->\t\tDESTROY$(END)\n"
		@$(MAKE) clean -C $(LIB)
		@$(MAKE) clean -C $(MLX)

fclean :	clean
			@$(MAKE) fclean -C $(LIB)
			@$(MAKE) imgclean
			@rm -f libmlx.dylib
			@printf "$(ERASE)$(RED)libmlx.dylib\t->\t\tDESTROY$(END)\n"
			@rm -f $(NAME)

re : fclean all

norme:
			@norminette $(SRCS) $(INCLUDES)
			@echo "\033[1;34mcub3d\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
			$(MAKE) norme -C ./libft

.PHONY : re all clean fclean norme

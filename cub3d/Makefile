# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 18:59:35 by grivalan          #+#    #+#              #
#    Updated: 2021/03/08 17:43:51 by grivalan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

NAME =		Cub3D

NAME2	=	Cub3Dlinux

LIB  =		./libft

MLX  =		./mlx

SRCS =		main.c\
			srcs/load/ft_load.c\
			srcs/load/file/ft_init_file.c\
			srcs/load/file/parsing_file.c\
			srcs/load/file/ft_file_to_struct.c\
			srcs/load/file/error_file.c\
			srcs/load/map/check_map.c\
			srcs/load/map/ft_map_cpy.c\
			srcs/load/map/ft_scan_map.c\
			srcs/load/map/ft_create_plane.c\
			srcs/load/planes/ft_search_plane.c\
			srcs/load/planes/ft_sort_planes.c\
			srcs/load/planes/ft_lst_planes_to_tab.c\
			srcs/load/file/ft_image_generate.c\
			srcs/load/screen/ft_screen.c\
			srcs/load/file/ft_check_struct.c\
			srcs/view/ft_init_tab_vector.c\
			srcs/sprite/ft_rotate_vectors_collides.c\
			srcs/view/ft_translation_vector.c\
			srcs/sprite/init_player.c\
			srcs/sprite/init_ennemy.c\
			srcs/sprite/ft_ennemy_to_list.c\
			srcs/sprite/ft_edit_sprite_plan.c\
			srcs/clear/clear_file.c\
			srcs/tools/ft_color_generate.c\
			srcs/tools/ft_delta_time_generator.c\
			srcs/update/ft_update.c\
			srcs/draw/ft_draw.c\
			srcs/draw/ft_pixel_color.c\

CC = gcc

ifeq ($(UNAME), Linux)
CFLAGS =	-Wall -Wextra -Werror -Ofast -D LINUX
else
CFLAGS =	-Wall -Wextra -Werror -Ofast -g
endif

INCLUDES =	includes

OBJS =		$(SRCS:.c=.o)

%.o: %.c includes/cub3d.h libft/libft.h includes/control_mac.h includes/control_linux.h
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDES)

$(NAME):	$(OBJS)
		$(MAKE) -C $(LIB)
		$(MAKE) -C $(MLX)
		cp mlx/libmlx.dylib .
		$(CC) -g3 -fsanitize=address -o $(NAME) $(OBJS) -I $(INCLUDES) libft/libft.a -Lmlx -lmlx -lm

$(NAME2) :	$(OBJS)
		$(MAKE) -C $(LIB)
		$(CC) -o $(NAME) $(OBJS) -I $(INCLUDES) libft/libft.a -lmlx -lm -lbsd -lX11 -lXext

all :		$(NAME)

linux :		$(NAME2)

clean :
		rm -rf $(OBJS)
		$(MAKE) clean -C $(LIB)
		$(MAKE) clean -C $(MLX)

fclean :	clean
			$(MAKE) fclean -C $(LIB)
			rm -f libmlx.dylib
			rm -f $(NAME)

re : fclean all

norme:
			@norminette $(SRCS) $(INCLUDES)
			@echo "\033[1;34mcub3d\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
			$(MAKE) norme -C ./libft

.PHONY : re all clean fclean norme

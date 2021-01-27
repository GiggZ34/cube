# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 18:59:35 by grivalan          #+#    #+#              #
#    Updated: 2021/01/25 12:28:57 by grivalan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME =		Cub3D

LIB  =		./libft

MLX  =		./mlx

SRCS =		main.c\
			srcs/load/ft_load.c\
			srcs/load/file/ft_init_file.c\
			srcs/load/file/parsing_file.c\
			srcs/load/file/ft_file_to_struct.c\
			srcs/load/file/error_file.c\
			srcs/load/map/check_map.c\
			srcs/load/map/ft_modif_map.c\
			srcs/load/builds/create_builds.c\
			srcs/load/map/ft_scan_map.c\
			srcs/load/map/ft_create_plane.c\
			srcs/load/builds/delete_builds.c\
			srcs/load/file/ft_image_generate.c\
			srcs/load/screen/ft_screen.c\
			srcs/load/file/ft_check_struct.c\
			srcs/sprite/init_player.c\
			srcs/sprite/init_ennemy.c\
			srcs/mini_map/mini_map.c\
			srcs/clear/clear_file.c\
			srcs/tools/ft_color_generate.c\
			srcs/draw/ft_draw.c

CC = gcc

CFLAGS =		-Wall -Wextra -Werror

INCLUDES =	includes

OBJS =		$(SRCS:.c=.o)

%.o: %.c includes/cub3d.h
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDES)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB)
			$(MAKE) -C $(MLX)
			cp mlx/libmlx.dylib .
			$(CC) -g3 -fsanitize=address -o $(NAME) $(OBJS) -I $(INCLUDES) libft/libft.a -Lmlx -lmlx -lm

all :		$(NAME)

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

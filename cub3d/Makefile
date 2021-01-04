# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 18:59:35 by grivalan          #+#    #+#              #
#    Updated: 2021/01/02 12:26:02 by grivalan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME =		Cub3D.out

LIB  =		./libft

SRCS =		main.c\
			file_treatment/parsing_file.c\
			file_treatment/ft_file_to_struct.c\
			file_treatment/error_file.c\
			file_treatment/check_map.c\
			file_treatment/ft_modif_map.c\

CC = gcc

FLAGS =		-Wall -Wextra -Werror

INCLUDES =	includes

OBJS =		$(SRCS:.c=.o)

%.o: %.c includes/cub3d.h
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDES)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB)
			$(CC) -o $(NAME) $(OBJS) libft/libft.a

all :		$(NAME)

clean :
		rm -rf $(OBJS)
		$(MAKE) clean -C ./libft

fclean :	clean
			$(MAKE) fclean -C ./libft
			rm -f $(NAME)

re : fclean all

norme:
			@norminette $(SRCS) $(INCLUDES)
			@echo "\033[1;34mcub3d\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
			$(MAKE) norme -C ./libft

.PHONY : re all clean fclean norme

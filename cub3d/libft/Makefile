# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 18:59:35 by grivalan          #+#    #+#              #
#    Updated: 2021/03/31 18:06:51 by grivalan         ###   ########lyon.fr    #
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

SRCS		=	ft_calloc.c\
				ft_realloc.c\
				ft_isalnum.c\
				ft_islower.c\
				ft_itoa.c\
				ft_lstclear.c\
				ft_lstmap.c\
				ft_memchr.c\
				ft_memset.c\
				ft_putstr_fd.c\
				ft_str_repeat.c\
				ft_strcpy.c\
				ft_strlcat.c\
				ft_strncmp.c\
				ft_substr.c\
				ft_abs.c\
				ft_min.c\
				ft_max.c\
				ft_sort_numbers.c\
				ft_char_to_str.c\
				ft_isalpha.c\
				ft_isprint.c\
				ft_itoa_base.c\
				ft_lstdelone.c\
				ft_lstclearone.c\
				ft_lst_swap.c\
				ft_lstnew.c\
				ft_memcmp.c\
				ft_putchar_fd.c\
				ft_putstr_repeat.c\
				ft_str_to_lower.c\
				ft_strcpypos.c\
				ft_strlcpy.c\
				ft_strnstr.c\
				ft_tolower.c\
				ft_atoi.c\
				ft_dechex.c\
				ft_isascii.c\
				ft_isupper.c\
				ft_lstadd_back.c\
				ft_lstiter.c\
				ft_lstsize.c\
				ft_memcpy.c\
				ft_putendl_fd.c\
				ft_split.c\
				ft_str_to_upper.c\
				ft_strdup.c\
				ft_strlen.c\
				ft_strrchr.c\
				ft_toupper.c\
				ft_bzero.c\
				ft_in_array.c\
				ft_isdigit.c\
				ft_iswhitespace.c\
				ft_lstadd_front.c\
				ft_lstlast.c\
				ft_memccpy.c\
				ft_memmove.c\
				ft_putnbr_fd.c\
				ft_str_pad.c\
				ft_strchr.c\
				ft_strjoin.c\
				ft_strmapi.c\
				ft_strtrim.c\
				ft_strpos.c\
				get_next_line.c\
				ft_count_words.c\
				ft_count_array.c\
				ft_strstr.c\
				ft_free_array.c\
				ft_nsplit.c\
				ft_intersect_plane_dot.c\
				ft_size_vec_plane.c\
				ft_create_vector.c\
				ft_deg_to_rad.c\
				ft_rotate_vector.c\
				ft_norm_vector_calculate.c\
				ft_dot_product.c\
				ft_normalize_vector.c\
				ft_vec_norm_define.c\
				ft_decbin.c\
				ft_plane_inter_nom.c\
				file_name_gen.c\

INCLUDES	=	libft.h

OBJS		=	$(SRCS:.c=.o)

NAME		=	libft.a

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra -Ofast -flto -march=native -ffast-math

%.o: %.c libft.h
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			@printf "$(ERASE)$(YELLOW)$<"

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)
			@printf "$(ERASE)$(GREEN)LIBFT\t\t->\t\tCOMPILED\n$(END)"

all:	$(NAME)

clean:
		@$(RM) $(OBJS)
		@printf "$(ERASE)$(RED)LIBFT\t\t->\t\tDESTROY$(END)\n"

fclean:	clean
		@$(RM) $(NAME)
		@printf "$(ERASE)$(RED)LIBFT.a\t\t->\t\tDESTROY$(END)\n"

re:		fclean all

norme:
			@norminette $(SRCS) $(INCLUDES)
			@echo "\033[1;34mlibft\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"

.PHONY:	all clean fclean re

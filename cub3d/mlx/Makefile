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

MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-Ofast -flto -march=native -ffast-math

NAME=libmlx.dylib

INC=-I.
OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
	@printf "$(ERASE)$(GREEN)MLX\t\t->\t\tCOMPILED\n$(END)"

%.o: %.c mlx.h
	@gcc $(CFLAGS) -c $< -o $(<:.c=.o)
	@printf "$(ERASE)$(YELLOW)$<$(END)"

%.o: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
	@printf "$(ERASE)$(YELLOW)$<$(END)"

%.swiftmodule: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
	@printf "$(ERASE)$(YELLOW)$<$(END)"

clean:
	@rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
	@printf "$(ERASE)$(RED)MLX\t\t->\t\tDESTROY\n$(END)"


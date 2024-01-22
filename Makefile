# Variables
CC					=	gcc
CFLAGS				=	-Wall -Wextra -Iinc -Isrc -O3 -g -I/usr/X11/include #-fsanitize=address -fno-omit-frame-pointer

RM					=	rm -rf
CUB3D				=   cub3D
NAME				=	$(CUB3D)

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/include

MLX_DIR				=	lib/mlx
MLX_FILE			=	$(MLX_DIR)/libmlx.a
CFLAGS				+=	-I $(MLX_DIR)
LDFLAGS				+=	-L $(MLX_DIR) -L /usr/X11/lib -lmlx -framework OpenGL -framework AppKit -lX11

MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH			=	src:include:src/mlx_functions:src/parser:src/geometry:src/utils:include
CUB3D_INC		=	CUB3D.h
CUB3D_SRC		=	$(shell find src -name '*.c')

# Object Files
OBJ_DIR				=	obj
CUB3D_OBJ		=	$(addprefix $(OBJ_DIR)/, $(CUB3D_SRC:.c=.o))

# Rules
all:				$(NAME)

$(OBJ_DIR)/%.o:		%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)

$(MLX_FILE):
					@$(MAKE_LIB) $(MLX_DIR)

$(NAME):			$(LIBFT_FILE) $(MLX_FILE) $(CUB3D_OBJ)
					@$(CC) $(CFLAGS) $(LDFLAGS) $(LIBFT_FILE) $(MLX_FILE) $(CUB3D_OBJ) -o $@
					@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean
					$(MAKE_LIB) $(MLX_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean
					$(MAKE_LIB) $(MLX_DIR) clean

clean:				lib_clean
					$(RM) $(OBJ_DIR)
					@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:				clean lib_fclean
					$(RM) $(NAME)
					@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"
					
re:					fclean all

# COLORS DEFINITION
RED				= \033[1;31m
DEFAULT			= \033[0m
GREEN			= \033[1;32m
BOLD			= \033[1m
YELLOW			= \033[1;33m

# Valgrind testing
valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

# Leaks at exit testing
leaks: $(NAME)
	$(LEAKS) ./$(NAME)

.SILENT:

.PHONY:				all lib_clean lib_fclean clean fclean re

# COLORS DEFINITION
RED				= \033[1;31m
DEFAULT			= \033[0m
GREEN			= \033[1;32m
BOLD			= \033[1m
YELLOW			= \033[1;33m
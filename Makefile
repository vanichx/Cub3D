# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 10:08:57 by ipetruni          #+#    #+#              #
#    Updated: 2024/01/15 10:38:52 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	gcc
CFLAGS				=	-Wall -Wextra -Iinclude -Isrc -O3 -g -fsanitize=address -fno-omit-frame-pointer

RM					=	rm -rf
CUB3D				=   cub3D
NAME				=	$(cub3D)

# readline, leaks, valgrind
VALGRIND			= valgrind --track-fds=yes --trace-children=yes#--log-file="valog" #--leak-check=full  -s --show-leak-kinds=all #--track-origins=yes
LEAKS				= leaks --atExit --

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/include

MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH				=	src:include:src/execution:src/lexer:src/parenthesis:src/parsing:src/expander:src/tree:src/utils:include
CUB3D_INC			=	CUB3D.h
CUB3D_SRC			=	$(shell find src -name '*.c')

# Object Files
OBJ_DIR				=	obj
CUB3D_OBJ			=	$(addprefix $(OBJ_DIR)/, $(CUB3D_SRC:.c=.o))

# Rules
all:				$(NAME)

$(OBJ_DIR)/%.o:		%.c $(CUB3D_INC)
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)

$(NAME):			$(LIBFT_FILE) $(CUB3D_OBJ)
					@$(CC) $(CFLAGS) $(LIBFT_FILE) $(CUB3D_OBJ) $(RL_LIBS) -o $@
					@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean

clean:				lib_clean
					$(RM) $(OBJ_DIR)
					@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:				clean lib_fclean
					$(RM) $(NAME)
					@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"
					
re:					fclean all

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 16:54:39 by ipetruni          #+#    #+#              #
#    Updated: 2024/01/15 17:35:59 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP OF THE PROGRAM

NAME = cub3D

# FILES AND PATH TO THEM

OBJ_DIR = obj/
SRC_DIR = src/
GNL_DIR = gnl/
MLX_DIR = mlx/

SRC	=	main \
		utils

SRCS =  $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
SRCS += $(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c)	
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
OBJS += $(addprefix $(OBJ_DIR), get_next_line.o get_next_line_utils.o)

# COMMANDS

CC = gcc 
CFLAGS = -Wall -Wextra -Werror -Imlx -I$(MLX_DIR) -I$(GNL_DIR)
LFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)
	@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(OBJ_DIR)get_next_line.o: $(GNL_DIR)get_next_line.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)get_next_line_utils.o: $(GNL_DIR)get_next_line_utils.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
		@$(RM) $(OBJS)
		@$(RM) $(OBJ_DIR)
		@echo "$(YELLOW)$(NAME) objects files deleted!$(DEFAULT)"
	
fclean: clean
		@$(RM) $(NAME)
		@echo "$(RED)$(NAME) program and objects deleted!$(DEFAULT)"

re:		fclean all

.PHONY: all clean fclean re

# COLORS DEFENITIONS

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m
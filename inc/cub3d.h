/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/12 12:27:39 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include <math.h>
#include "libft.h"
#include "geo.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <X11/Xlib.h>

// ------------------------ MINILIBX ----------------------------

# ifdef __APPLE__
#  include "../lib/mlx_mac/mlx.h"
#  include "keycodes_mac.h"
#  define PLATFORM "mac"
# else
#  include "../lib/mlx_linux/mlx.h"
#  include "keycodes_linux.h"
#  define PLATFORM "linux"
# endif


#define MAX_LINES 10000


# define EXPAND 1
# define REDUCE 0

# define MAPSCALE 64
# define MAX_NUM_TEXT 4
# define COLORS_COMPONENTS 3

/* main.c */
void	check_args(int argc, char *argv[]);
void	parse(char *map_path, t_cube *cube);

/* ../src/parser */

/* gnl.c */
char	*get_next_line(int fd);

/* init.c */
void	init_cube(t_cube *cube);
void	init_window(t_cube *cube);

/* parse_colors.c */
int		parse_color_code(char *line, int *color);

/* parse_file.c */
void	parse_file(char *map_path, char ***map_file, t_cube *cube);

/* parse_info.c */
void	parse_textures(char *trimmed_line, t_cube *cube);
void	parse_floor_color(char *trimmed_line, t_cube *cube);
void	parse_ceiling_color(char *trimmed_line, t_cube *cube);
void	parse_map_lines(char *line, char **buffer, t_cube *cube);
void	print_map_info(t_cube *cube); //DEBUG

/* parse_map.c */
void	parse_map(char **map_file, t_cube *cube);

/* parse_player.c */
void	parse_player(t_cube *cube);
void	check_walls(t_cube *cube);

/* parse_utils.c */
bool	is_valid_char(char c);
int		is_valid_line(char *line, t_cube *cube);
int		read_file(char *map_path, int *fd);
bool	line_has_walls(char *line);
int		is_player(char *line);

/* ../src/parser */




/*****************************************	utils	******************************************/
/* utils.c */
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_isspace(int c);
char	*trim_whitespace(const char *str);
char	*custom_strdup(const char *src);
/*****************************************	utils	******************************************/



/*************************************	mlx_functions	**************************************/

int render(t_cube *cube);


/* resize_window.c */
void resize_window(t_cube *cub, int flag);

/* cleanup.c */
void	ft_strdel(char **s);
void	free_textures(t_cube *cube);
void	free_2darray(void **array);
int	cleanup(t_cube *cube, int exit_code);
void	exit_program(t_cube *cube, int exit_code, char *message);

/* mouse_events.c */
int		mouse_release(int button, int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);

/* hooking.c */
bool	hooking(t_cube *cube);

/* key_hooks.c */
int key_press(int key, void *param);
int key_release(int key, void *param);
/*************************************	mlx_functions	**************************************/

#endif
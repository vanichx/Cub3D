/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 09:32:07 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "keycodes.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define WIDTH 1920
#define HEIGHT 1080
#define MAX_LINES 10000

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define PLAYER_SPEED 10
#define PLAYER_ROT_SPEED 4

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}		t_point;

typedef	struct s_mlx
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_map
{
	char	*texture[4];
	int		floor_col[3];
	int		ceiling_col[3];
	char	**map_file;
	char	**map;
	int 	map_width;
	int		map_height;
	int 	num_line;
	int		num_textures;
	int		map_x;
	int		map_y;
}				t_map;

typedef struct s_player
{
	t_point		pos;
	t_point		matrix_pos;
	int			move;
	int			rotate;
	float		player_speed;
	float		player_rot_speed;
	char		init_view;
} 			t_player;

typedef struct s_cube
{
	t_mlx		screen;
	t_player	player;
	t_map		map;
	int			fov;
}			t_cube;

/* main.c */
bool	check_args(int argc, char *argv[]);
bool	parse(char *map_path, t_cube *cube);


/*****************************************	PARSER	******************************************/
/* parse_file.c */
int		parse_file(char *map_path, char ***map_file);

/* parse_map.c */
int		parse_map(char **map_file, t_cube *cube);

/* parse_info.c */
void	parse_textures(char *trimmed_line, t_cube *cube);
void	parse_floor_color(char *trimmed_line, t_cube *cube, char *line);
void	parse_ceiling_color(char *trimmed_line, t_cube *cube, char *line);
int		parse_map_lines(char *line, char **buffer, t_cube *cube);
void	print_map_info(t_cube *cube);

/* parse_colors.c */
int		parse_color_code(char *line, int *color);

/* parse_utils.c */
bool	is_valid_char(char c);
int		is_valid_line(char *line);
int		read_file(char *map_path, int *fd);
bool	line_has_walls(char *line);
int		is_player(char *line);

/* parse_player.c */
int		parse_player(t_cube *cube);
int 	check_walls(char **map, int map_height, int map_width);

/* gnl.c */
char	*get_next_line(int fd);

/* init.c */
void	init_cube(t_cube *cube);
bool	init_window(t_mlx *screen);
/*****************************************	PARSER	******************************************/



/*****************************************	utils	******************************************/
/* utils.c */
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_isspace(int c);
char	*trim_whitespace(const char *str);
/*****************************************	utils	******************************************/



/*****************************************	free	******************************************/
/* free.c */
void	ft_strdel(char **s);
void	free_textures(t_cube *cube);
void	free_2darray(char **array);
void	cleanup(t_cube *cube);
/*****************************************	free	******************************************/

#endif
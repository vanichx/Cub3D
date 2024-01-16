/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 18:31:49 by ipetruni         ###   ########.fr       */
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

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

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
	char	**map;
	int 	map_width;
	int		map_height;
	int 	num_line;
	int		num_textures;
	int		data_type;
	bool	map_parsing;
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






/* parse_map.c */
void	init_all(t_cube *cube);
int		read_file(char *map_path, int *fd);
int		validate_map_line(char *line);
int		handle_map_file(int fd, char **map, t_cube *cube);
int 	update_map_and_player_info(char *line, t_cube *cube, char **map);
bool	line_has_wall(char *line);
int		find_player_position(char *line, t_cube *cube);
bool	find_valid_character(char c);
bool	is_player_direction(char ch);
bool	parse_and_init(char *map_path, t_cube *cube);


/* gnl.c */
int		ft_linelen(char *s);
char	*ft_extract_line(char *buffer);
char	*ft_read(int fd, char *buffer);
char	*ft_remove_line(char *buffer);
char	*get_next_line(int fd);


/* utils.c */
void	*ft_realloc(void *ptr, size_t size);


#endif
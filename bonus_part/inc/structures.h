/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:48 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/27 16:29:49 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>
# include "libft.h"

# define X 0
# define Y 1

# define PLAYER_SPEED 0.05
# define PLAYER_ROT_SPEED 0.05

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5

# define START 0
# define END 1

# define OLD 0
# define NEW 1

# define TEXT_SIZE 64

# define LIFE_S 0
# define KEY_STATUS 1

# define KNIFE 0
# define GUN 1

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}		t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		*casted_addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	int		width;
	int		height;
	int		default_w;
	int		default_h;
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_map
{
	char	*texture[6];
	char	**map_file;
	char	**map;
	int		map_width;
	int		map_height;
	int		num_line;
	int		num_textures;
	int		map_x;
	int		map_y;
}				t_map;

typedef struct s_vec
{
	double	dir[2];
}		t_vec;

typedef struct s_ray
{
	double	camera_x;
	t_vec	ray_dir;
	t_vec	ray_dir_l;
	t_vec	ray_dir_r;
	int		map_point[2];
	int		step[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw[2];
}	t_ray;

typedef struct s_player
{
	double	pos[2];
	t_point	m_pos;
	t_vec	front;
	t_vec	cam;
	int		player_height;
	int		move[2];
	double 	time[2];
	double	frame_time;
	double	rotate;
	double	player_speed;
	double	player_rot_speed;
	char	init_v;
	double	sub_angles;
	float	fov;
	int		info[2];
	t_ray	ray;
}			t_player;

typedef struct s_textures
{
	t_img	img_text[6];
	int		*textures[6];
	int		text_point[2];
	double	tex_step;
	double	tex_pos;
	int		tex_size;
}		t_textures;

typedef struct s_keys
{
	int		key_esc;
	int		key_s;
	int		key_w;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		key_i;
	int		key_o;
}      t_keys;

typedef struct s_minimap
{
	char	**map;
	t_point	m_pos;
	t_img	*img;
	int		view_dist;
	int		size;
	int		offset_x;
	int		offset_y;
	int		tile_size;
	int		show;
}			t_minimap;

typedef struct s_door
{
	int    is;
	int    text_x;
	int    x;
	int    *actx;
}				t_door;

typedef struct s_dsprite
{
	double	transform[2];
	int		start[2];
	int		end[2];
	int		h;
	int		w;
	int		tex_x;
	int 	screen_x;
}				t_dsprite;

typedef struct s_cube
{
	t_mlx			screen;
	t_player		player;
	t_map			map;
	t_textures		wall_text;
	t_textures		sprite_text;
	t_img			minimap;
	t_minimap		minimap_data;
	t_door			door;
	t_keys			key;
	int 			**text_pixels;
	int				player_has_moved;
}			t_cube;


#endif

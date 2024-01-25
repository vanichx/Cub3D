#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define X 0
#define Y 1

#define PLAYER_SPEED 10
#define PLAYER_ROT_SPEED 4

#define DEG_TO_RAD(angle) (angle * M_PI / 180)

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
	int		default_w;
	int		default_h;
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

typedef struct	s_vec
{
	float dir[2];
}		t_vec;

typedef struct s_player
{
	t_point	pos;
	t_point	m_pos;
	t_vec	front;
	t_vec	cam;
	bool	move;
	bool	rotate;
	float	player_speed;
	float	player_rot_speed;
	char	init_view;
} 			t_player;

typedef struct s_cube
{
	t_mlx		screen;
	t_player	player;
	t_map		map;
	int			fov;
}			t_cube;

#endif

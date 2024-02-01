#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

#define X 0
#define Y 1

#define PLAYER_SPEED 10
#define PLAYER_ROT_SPEED 4

#define NO 0
#define SO 1
#define EA 2
#define WE 3



#define DEG_TO_RAD(angle) (angle * M_PI / 180)

typedef struct s_point
{
	float	x;
	float	y;
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
	double dir[2];
}		t_vec;

typedef struct s_wall_text
{
	int		valid;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_wall_text;


typedef struct s_player
{
	t_point	pos;
	t_point	m_pos;
	t_vec	front;
	t_vec	cam;
	int		player_height;
	bool	move;
	bool	rotate;
	float	player_speed;
	float	player_rot_speed;
	char	init_view;
	double	fov;
	double	sub_angles;
} 			t_player;

typedef struct s_grid
{
	t_point center;
	int		size;
	void	*img_text[4];
}		t_grid;

typedef struct s_cube
{
	t_mlx		screen;
	t_player	player;
	t_map		map;
	t_grid		grid;
	t_wall_text wall_text[4];
}			t_cube;


#endif

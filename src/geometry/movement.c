#include "cub3d.h"

void move_forward(t_cube *cube)
{
	int delta_x;
	int delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[X] * (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[Y] * (cube->player.player_speed * 2));

	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] += cube->player.front.dir[X] * cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] += cube->player.front.dir[Y] * cube->player.player_speed;
}

void move_backward(t_cube *cube)
{
	int delta_x;
	int delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[X] * (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[Y] * (cube->player.player_speed * 2));

	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] -= cube->player.front.dir[X] * cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] -= cube->player.front.dir[Y] * cube->player.player_speed;
}

void move_left(t_cube *cube)
{
	int delta_x;
	int delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[Y] * (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[X] * (cube->player.player_speed * 2));

	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] += cube->player.front.dir[Y] * cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] -= cube->player.front.dir[X] * cube->player.player_speed;
}

void move_right(t_cube *cube)
{
	int delta_x;
	int delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[Y] * (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[X] * (cube->player.player_speed * 2));

	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] -= cube->player.front.dir[Y] * cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] += cube->player.front.dir[X] * cube->player.player_speed;
}

void rotate_left(t_cube *cube)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	cube->player.front.dir[X] = cube->player.front.dir[X] * cos(-cube->player.player_rot_speed) - cube->player.front.dir[Y] * sin(-cube->player.player_rot_speed);
	cube->player.front.dir[Y] = old_dir_x * sin(-cube->player.player_rot_speed) + cube->player.front.dir[Y] * cos(-cube->player.player_rot_speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(-cube->player.player_rot_speed) - cube->player.cam.dir[Y] * sin(-cube->player.player_rot_speed);
	cube->player.cam.dir[Y] = old_plane_x * sin(-cube->player.player_rot_speed) + cube->player.cam.dir[Y] * cos(-cube->player.player_rot_speed);
}

void rotate_right(t_cube *cube)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	cube->player.front.dir[X] = cube->player.front.dir[X] * cos(cube->player.player_rot_speed) - cube->player.front.dir[Y] * sin(cube->player.player_rot_speed);
	cube->player.front.dir[Y] = old_dir_x * sin(cube->player.player_rot_speed) + cube->player.front.dir[Y] * cos(cube->player.player_rot_speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(cube->player.player_rot_speed) - cube->player.cam.dir[Y] * sin(cube->player.player_rot_speed);
	cube->player.cam.dir[Y] = old_plane_x * sin(cube->player.player_rot_speed) + cube->player.cam.dir[Y] * cos(cube->player.player_rot_speed);
	
	
}
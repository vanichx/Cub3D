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

// int rotate_left_right(t_cube *cube, double rootspeed)
// {
// 	double tmp_x;

// 	tmp_x = cube->player.front.dir[X];
// 	cube->player.front.dir[X] = cube->player.front.dir[X] * cos(rootspeed) - cube->player.front.dir[Y] * sin(rootspeed);
// 	cube->player.front.dir[Y] = tmp_x * sin(rootspeed) + cube->player.front.dir[Y] * cos(rootspeed);
// 	tmp_x = cube->player.cam.dir[X];
// 	cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(rootspeed) - cube->player.cam.dir[Y] * sin(rootspeed);
// 	cube->player.cam.dir[Y] = tmp_x * sin(rootspeed) + cube->player.cam.dir[Y] * cos(rootspeed);
// 	return (1);
// }

// int rotate(t_cube *cube, int dir)
// {
// 	int moved;
// 	double rootspeed;

// 	moved = 0;
// 	rootspeed = cube->player.player_rot_speed * dir;
// 	moved += rotate_left_right(cube, rootspeed);
// 	return (moved);
// }

#include "cub3d.h"

static bool	is_valid_pos_in_map(t_cube *cube, double x, double y)
{
	if (x < 0.25 || x >= cube->map.map_width - 1.25)
		return (false);
	if (y < 0.25 || y >= cube->map.map_height -0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_cube *cube, double x, double y)
{
	if (is_valid_pos_in_map(cube, x, y))
		return (true);
	return (false);
}

int	validate_move(t_cube *cube, double new[2])
{
	int	moved;

	moved = 0;
	if (is_valid_pos(cube, new[X], cube->player.pos[Y]))
	{
		cube->player.pos[X] = new[X];
		moved = 1;
	}
	if (is_valid_pos(cube, cube->player.pos[X], new[Y]))
	{
		cube->player.pos[Y] = new[Y];
		moved = 1;
	}
	return (moved);
}

int move_forward(t_cube *cube)
{
    double new[2];
    printf("cube->player.player_speed: %lf\n", cube->player.player_speed);
    new[X] = cube->player.pos[X] + cube->player.front.dir[X] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] + cube->player.front.dir[Y] * cube->player.player_speed;
    return (validate_move(cube, new));
}

int move_backward(t_cube *cube)
{
    double new[2];

    new[X] = cube->player.pos[X] - cube->player.front.dir[X] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] - cube->player.front.dir[Y] * cube->player.player_speed;
    return (validate_move(cube, new));
}

int move_left(t_cube *cube)
{
    double new[2];

    new[X] = cube->player.pos[X] + cube->player.front.dir[Y] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] - cube->player.front.dir[X] * cube->player.player_speed;
    return (validate_move(cube, new));
}

int move_right(t_cube *cube)
{
    double new[2];

    new[X] = cube->player.pos[X] - cube->player.front.dir[Y] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] + cube->player.front.dir[X] * cube->player.player_speed;
    return (validate_move(cube, new));
}

int rotate_left_right(t_cube *cube, double rootspeed)
{
    double tmp_x;

    tmp_x = cube->player.front.dir[X];
    cube->player.front.dir[X] = cube->player.front.dir[X] * cos(rootspeed) - cube->player.front.dir[Y] * sin(rootspeed);
    cube->player.front.dir[Y] = tmp_x * sin(rootspeed) + cube->player.front.dir[Y] * cos(rootspeed);
    tmp_x = cube->player.cam.dir[X];
    cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(rootspeed) - cube->player.cam.dir[Y] * sin(rootspeed);
    cube->player.cam.dir[Y] = tmp_x * sin(rootspeed) + cube->player.cam.dir[Y] * cos(rootspeed);
    return (1);
}

int rotate(t_cube *cube, int dir)
{
    int moved;
    double rootspeed;

    moved = 0;
    rootspeed = cube->player.player_rot_speed * dir;
    moved += rotate_left_right(cube, rootspeed);
    return (moved);
}

int move_player(t_cube *cube)
{
    int moved;

    moved = 0;
    if (cube->player.move[Y] == 1)
        moved += move_forward(cube);
    if (cube->player.move[Y] == -1)
        moved += move_backward(cube);
    if (cube->player.move[X] == 1)
        moved += move_right(cube);
    if (cube->player.move[X] == -1)
        moved += move_left(cube);
    if (cube->player.rotate != 0)
        moved += rotate(cube, cube->player.rotate);
    return (moved);
}
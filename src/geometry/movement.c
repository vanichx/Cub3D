#include "cub3d.h"

int move_forward(t_cube *cube)
{
    int moved;
    double new[2];

    new[X] = cube->player.pos[X] + cube->player.front.dir[X] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] + cube->player.front.dir[Y] * cube->player.player_speed;
    moved = 0;
    if (new[X] >= 0.25 && new[X] < cube->map.map_width - 1.25)
    {
        cube->player.pos[X] = new[X];
        moved = 1;
    }
    if (new[Y] >= 0.25 && new[Y] < cube->map.map_height - 0.25)
    {
        cube->player.pos[Y] = new[Y];
        moved = 1;
    }
    return (moved);
}

int move_backward(t_cube *cube)
{
    int moved;
    double new[2];

    new[X] = cube->player.pos[X] - cube->player.front.dir[X] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] - cube->player.front.dir[Y] * cube->player.player_speed;
    moved = 0;
    if (new[X] >= 0.25 && new[X] < cube->map.map_width - 1.25)
    {
        cube->player.pos[X] = new[X];
        moved = 1;
    }
    if (new[Y] >= 0.25 && new[Y] < cube->map.map_height - 0.25)
    {
        cube->player.pos[Y] = new[Y];
        moved = 1;
    }
    return (moved);
}

int move_left(t_cube *cube)
{
    int moved;
    double new[2];

    new[X] = cube->player.pos[X] + cube->player.front.dir[Y] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] - cube->player.front.dir[X] * cube->player.player_speed;
    moved = 0;
    if (new[X] >= 0.25 && new[X] < cube->map.map_width - 1.25)
    {
        cube->player.pos[X] = new[X];
        moved = 1;
    }
    if (new[Y] >= 0.25 && new[Y] < cube->map.map_height - 0.25)
    {
        cube->player.pos[Y] = new[Y];
        moved = 1;
    }
    return (moved);
}

int move_right(t_cube *cube)
{
    int moved;
    double new[2];

    new[X] = cube->player.pos[X] - cube->player.front.dir[Y] * cube->player.player_speed;
    new[Y] = cube->player.pos[Y] + cube->player.front.dir[X] * cube->player.player_speed;
    moved = 0;
    if (new[X] >= 0.25 && new[X] < cube->map.map_width - 1.25)
    {
        cube->player.pos[X] = new[X];
        moved = 1;
    }
    if (new[Y] >= 0.25 && new[Y] < cube->map.map_height - 0.25)
    {
        cube->player.pos[Y] = new[Y];
        moved = 1;
    }
    return (moved);
}

int rotate_right(t_cube *cube)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = cube->player.front.dir[X];
    cube->player.front.dir[X] = cube->player.front.dir[X] * cos(-cube->player.player_rot_speed) - cube->player.front.dir[Y] * sin(-cube->player.player_rot_speed);
    cube->player.front.dir[Y] = old_dir_x * sin(-cube->player.player_rot_speed) + cube->player.front.dir[Y] * cos(-cube->player.player_rot_speed);
    old_plane_x = cube->player.cam.dir[X];
    cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(-cube->player.player_rot_speed) - cube->player.cam.dir[Y] * sin(-cube->player.player_rot_speed);
    cube->player.cam.dir[Y] = old_plane_x * sin(-cube->player.player_rot_speed) + cube->player.cam.dir[Y] * cos(-cube->player.player_rot_speed);
    return (1);
}

int rotate_left(t_cube *cube)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = cube->player.front.dir[X];
    cube->player.front.dir[X] = cube->player.front.dir[X] * cos(cube->player.player_rot_speed) - cube->player.front.dir[Y] * sin(cube->player.player_rot_speed);
    cube->player.front.dir[Y] = old_dir_x * sin(cube->player.player_rot_speed) + cube->player.front.dir[Y] * cos(cube->player.player_rot_speed);
    old_plane_x = cube->player.cam.dir[X];
    cube->player.cam.dir[X] = cube->player.cam.dir[X] * cos(cube->player.player_rot_speed) - cube->player.cam.dir[Y] * sin(cube->player.player_rot_speed);
    cube->player.cam.dir[Y] = old_plane_x * sin(cube->player.player_rot_speed) + cube->player.cam.dir[Y] * cos(cube->player.player_rot_speed);
    return (1);
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
    if (cube->player.rotate == 1)
        moved += rotate_right(cube);
    if (cube->player.rotate == -1)
        moved += rotate_left(cube);
    return (moved);
}
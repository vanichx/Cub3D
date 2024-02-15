#include "cub3d.h"


void zoom_in(t_cube *c)
{
    double tan_half_fov_rad;

    c->player.fov += 1;
    tan_half_fov_rad = tan((c->player.fov * (M_PI / 180)) / 2);
    c->player.cam.dir[X] = -c->player.front.dir[Y] * tan_half_fov_rad;
    c->player.cam.dir[Y] = c->player.front.dir[X] * tan_half_fov_rad;
}

void zoom_out(t_cube *c)
{
    double tan_half_fov_rad;

    c->player.fov -= 1;
    tan_half_fov_rad = tan((c->player.fov * (M_PI / 180)) / 2);
    c->player.cam.dir[X] = -c->player.front.dir[Y] * tan_half_fov_rad;
    c->player.cam.dir[Y] = c->player.front.dir[X] * tan_half_fov_rad;
}

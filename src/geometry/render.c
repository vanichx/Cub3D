#include "cub3d.h"

int render_cube(t_cube *cube)
{
    init_ray(&cube->player.ray);
    raycast(cube, &cube->player.ray);
    render(cube);
    return (0);
}
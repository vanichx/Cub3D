#include "cub3d.h"

void init_ray(t_ray *ray)
{
    ray->step[X] = 0;
    ray->step[Y] = 0;
    ray->side_dist[X] = 0;
    ray->side_dist[Y] = 0;
    ray->wall_dist = 0;
    ray->wall_x = 0;
    ray->side = 0;
    ray->line_height = 0;
    ray->draw[START] = 0;
    ray->draw[END] = 0;
}

void    setup_ray_params(t_cube *cube, t_ray *ray, int x)
{
    ray->camera_x = 2 * x / (double)cube->screen.width - 1;
    ray->ray_dir.dir[X] = cube->player.front.dir[X] + cube->player.cam.dir[X] * ray->camera_x;
    ray->ray_dir.dir[Y] = cube->player.front.dir[Y] + cube->player.cam.dir[Y] * ray->camera_x;
    ray->map_point.x = (int)cube->player.pos.x;
    ray->map_point.y = (int)cube->player.pos.y;
    ray->delta_dist[X] = fabs(1 / ray->ray_dir.dir[X]);
    ray->delta_dist[Y] = fabs(1 / ray->ray_dir.dir[Y]);
}

void calculate_line_height(t_cube *cube, t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist[X] - ray->delta_dist[X]);
    else
        ray->wall_dist = (ray->side_dist[Y] - ray->delta_dist[Y]);
    ray->line_height = (int)(cube->screen.height / ray->wall_dist);
    ray->draw[START] = -ray->line_height / 2 + cube->screen.height / 2;
    if (ray->draw[START] < 0)
        ray->draw[START] = 0;
    ray->draw[END] = ray->line_height / 2 + cube->screen.height / 2;
    if (ray->draw[END] >= cube->screen.height)
        ray->draw[END] = cube->screen.height - 1;
    if(ray->side == 0)
        ray->wall_x = cube->player.pos.y + ray->wall_dist * ray->ray_dir.dir[Y];
    else
        ray->wall_x = cube->player.pos.x + ray->wall_dist * ray->ray_dir.dir[X];
    ray->wall_x -= floor(ray->wall_x);
}

int get_texture_index(t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->ray_dir.dir[X] < 0)
            return (WE);
        else
            return (EA);
    }
    else
    {
        if (ray->ray_dir.dir[Y] > 0)
            return (SO);
        else
            return (NO);
    }
}

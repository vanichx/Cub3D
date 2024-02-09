#include "cub3d.h"

void    setup_dda_params(t_cube *cube, t_ray *ray)
{
    if (ray->ray_dir.dir[X] < 0)
    {
        ray->step[X] = -1;
        ray->side_dist[X] = (cube->player.pos.x - ray->map_point.x) * ray->delta_dist[X];
    }
    else
    {
        ray->step[X] = 1;
        ray->side_dist[X] = (ray->map_point.x + 1.0 - cube->player.pos.x) * ray->delta_dist[X];
    }
    if (ray->ray_dir.dir[Y] < 0)
    {
        ray->step[Y] = -1;
        ray->side_dist[Y] = (cube->player.pos.y - ray->map_point.y) * ray->delta_dist[Y];
    }
    else
    {
        ray->step[Y] = 1;
        ray->side_dist[Y] = (ray->map_point.y + 1.0 - cube->player.pos.y) * ray->delta_dist[Y];
    }
}

void    perform_dda(t_cube *cube, t_ray *ray)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (ray->side_dist[X] < ray->side_dist[Y])
        {
            ray->side_dist[X] += ray->delta_dist[X];
            ray->map_point.x += ray->step[X];
            ray->side = 0;
        }
        else
        {
            ray->side_dist[Y] += ray->delta_dist[Y];
            ray->map_point.y += ray->step[Y];
            ray->side = 1;
        }
        if (ray->map_point.y < 0.25 || ray->map_point.x < 0.25
            || ray->map_point.y > cube->map.map_height - 0.25
            || ray->map_point.x > cube->map.map_width - 1.25)
            break;
        else if (cube->map.map[(int)ray->map_point.y][(int)ray->map_point.x] == '1')
            hit = 1;
    }
}

void update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
    int y;
    int color;
    int texture_index;

    texture_index = get_texture_index(ray);
    cube->wall_text.text_point[X] = (int)(ray->wall_x * TEXT_SIZE);
    if (((ray->side == 0) && (ray->ray_dir.dir[X] < 0))
        || ((ray->side == 1) && (ray->ray_dir.dir[Y] > 0)))
        cube->wall_text.text_point[X] = TEXT_SIZE - cube->wall_text.text_point[X] - 1;
    cube->wall_text.tex_step = 1.0 * TEXT_SIZE / ray->line_height;
    cube->wall_text.tex_pos = (ray->draw[START] - cube->screen.height / 2 + ray->line_height / 2) * cube->wall_text.tex_step;
    y = ray->draw[START];
    while (y < ray->draw[END])
    {
        cube->wall_text.text_point[Y] = (int)cube->wall_text.tex_pos & (TEXT_SIZE - 1);
        cube->wall_text.tex_pos += cube->wall_text.tex_step;
        color = cube->wall_text.textures[texture_index][TEXT_SIZE * cube->wall_text.text_point[Y] + cube->wall_text.text_point[X]];
        if (texture_index == NO || texture_index == EA)
            color = (color >> 1) & 8355711;
        if (color > 0)
            cube->wall_text.text_pixels[y][x] = color;
        y++;
    }
}


void raycast(t_cube *cube, t_ray *ray)
{
    int x;

    x = 0;
    while (x < cube->screen.width)
    {
        setup_ray_params(cube, ray, x);
        setup_dda_params(cube, ray);
        perform_dda(cube, ray);
        calculate_line_height(cube, ray);
        update_texts_pixels(cube, ray, x);
        x++;
    }
    render_frame(cube);
}
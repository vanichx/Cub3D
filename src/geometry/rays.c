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

void realloc_text_pixels(int *(*text_pixels)[4], t_cube *cube)
{
    int i;

    i = NO;
    while (i < EA)
    {
        if ((*text_pixels)[i] == NULL)
        {
            (*text_pixels)[i] = malloc(sizeof(int) * TEXT_SIZE * TEXT_SIZE);
            if (!(*text_pixels)[i])
                exit_program(cube, 1, MALLOC_ERROR);
        }
        else
        {
            (*text_pixels)[i] = realloc((*text_pixels)[i], sizeof(int) * TEXT_SIZE * TEXT_SIZE);
            if (!(*text_pixels)[i])
                exit_program(cube, 1, MALLOC_ERROR);
        }
        i++;
    }
}

void update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
    int y;
    int color;
    int texture_index;

    texture_index = get_texture_index(ray);
    cube->wall_text.text_point[X] = (int)(ray->wall_x * TEXT_SIZE);
    //printf("cube->wall_text.text_point[X]: %f\n", cube->wall_text.text_point[X]);
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
            if (y >= 0 && y < TEXT_SIZE && x >= 0 && x < TEXT_SIZE)
                cube->wall_text.text_pixels[y][x] = color;
        y++;
    }
}

void raycast(t_cube *cube, t_ray *ray)
{
    int x;

    x = 0;
    realloc_text_pixels(&cube->wall_text.text_pixels, cube);
    while (x < cube->screen.width)
    {
        setup_ray_params(cube, ray, x);
        setup_dda_params(cube, ray);
        perform_dda(cube, ray);
        calculate_line_height(cube, ray);
        update_texts_pixels(cube, ray, x);
        x++;
    }
}

int render_cube(t_cube *cube)
{
    init_ray(&cube->player.ray);
    raycast(cube, &cube->player.ray);

    render(cube);
    return (0);
}


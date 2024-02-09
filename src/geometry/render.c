#include "cub3d.h"

void    set_image_pixel(t_img *img, int i[2], int color, t_cube *cube)
{
    int pixel;

    if (i[X] >= 0 && i[X] < cube->screen.width && i[Y] >= 0 && i[Y] < cube->screen.height) {
        pixel = i[Y] * (img->line_length / 4) + i[X];
        img->casted_addr[pixel] = color;
    }
    else
        exit_program(cube, 1, "Error: pixel out of bounds");
}

void    set_frame_image_pixel(t_cube *cube, t_img *img, int i[2])
{
    if (cube->wall_text.text_pixels[i[Y]][i[X]] > 0)
        set_image_pixel(img, i, cube->wall_text.text_pixels[i[Y]][i[X]], cube);
    else if (i[Y] < cube->screen.height / 2)
        set_image_pixel(img, i, cube->map.c_col, cube);
    else if (i[Y] < cube->screen.height - 1 && i[Y] > cube->screen.height / 2)
        set_image_pixel(img, i, cube->map.f_col, cube);
}

void    render_frame(t_cube *cube)
{
    t_img   img;
    int     i[2];

    img.img = mlx_new_image(cube->screen.mlx, cube->screen.height, cube->screen.width);
    if (img.img == NULL)
        exit_program(cube, 1, MLX_IMG_ERROR);
    img.casted_addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
    i[Y] = -1;
    while (++i[Y] < cube->screen.height)
    {
        i[X] = -1;
        while (++i[X] < cube->screen.width)
            set_frame_image_pixel(cube, &img, i);
    }
    mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, img.img, 0, 0);
    mlx_destroy_image(cube->screen.mlx, img.img);
}

int render_cube(t_cube *cube)
{
    init_ray(&cube->player.ray);
    raycast(cube, &cube->player.ray);
    // render(cube);
    return (0);
}
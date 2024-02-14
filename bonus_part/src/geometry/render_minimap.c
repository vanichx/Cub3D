/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:30:03 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/14 15:17:46 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel_color(char *img_data, int x, int y, int color, int minimap_width) 
{
	int	i;
	int	pixel_x;
	int	pixel_y;
	int	scale;

	scale = MINIMAPSCALE;
	i = 0;
	while (i < scale) {
		int j = 0;
		while (j < scale) {
			pixel_x = x * scale + i;
			pixel_y = y * scale + j;
			((int *)img_data)[pixel_y * minimap_width + pixel_x] = color;
			j++;
		}
		i++;
	}
}

int	get_color(t_cube *cube, int x, int y) 
{
	int color;
	char cell;

	cell = cube->map.map[y][x];
	if (cell == '1') 
		color = 0xFFFFFF;
	else if (cell == '0')
		color = 0x000000;
	else
		color = 0x000000;
	return (color);
}

void	calculate_minimap_dimensions(t_cube *cube, int *width, int *height)
{
	*width = cube->screen.width / MINIMAPSCALE;
	*height = cube->screen.height / MINIMAPSCALE;
}

void	create_minimap_image(t_cube *cube, void **img_ptr, char **img_data, int width, int height)
{
	*img_ptr = mlx_new_image(cube->screen.mlx, width, height);
	*img_data = mlx_get_data_addr(*img_ptr, &cube->screen.img.bpp, &cube->screen.img.line_length, &cube->screen.img.endian);
}

void	render_minimap_pixels(t_cube *cube, char *img_data, int width)
{
	int y;
	int x;
	int color;

	y = 0;
	while (y < cube->map.map_height)
	{
		x = 0;
		while (x < cube->map.map_width - 1)
		{
			color = get_color(cube, x, y);
			set_pixel_color(img_data, x, y, color, width);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_cube *cube)
{
	int minimap_width;
	int minimap_height;
	void *img_ptr;
	char *img_data;

	calculate_minimap_dimensions(cube, &minimap_width, &minimap_height);
	create_minimap_image(cube, &img_ptr, &img_data, minimap_width  , minimap_height);
	render_minimap_pixels(cube, img_data, minimap_width);
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, img_ptr, cube->screen.width - minimap_width - 5, 5);
	mlx_destroy_image(cube->screen.mlx, img_ptr);
}
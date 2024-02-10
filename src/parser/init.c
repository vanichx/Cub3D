/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:18:59 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/10 13:07:08 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cube(t_cube *cube)
{
	int initial_fov;

	initial_fov = 60;
	cube->map.map_x = 0;
	cube->map.map_y = 0;
	cube->map.num_line = 0;
	cube->map.num_textures = 0;
	cube->player.pos[X] = 0;
	cube->player.pos[Y] = 0;
	cube->player.player_speed = 10;
	cube->player.player_rot_speed = 4;
	cube->player.fov = ang_to_rad(initial_fov);
	cube->wall_text.tex_size = TEXT_SIZE;
	cube->player.player_height = 32;
}

void	init_window(t_cube *cube)
{
	Display	*display;
	Screen	*s;

	display = XOpenDisplay(NULL);
	if (!display)
		exit_program(cube, EXIT_FAILURE, DISPLAY_ERROR);
	s = DefaultScreenOfDisplay(display);
	cube->screen.default_h = s->height;
	cube->screen.default_w = s->width;
	cube->screen.width = s->width;
	cube->screen.height = s->height;
	cube->screen.mlx = mlx_init();
	if (!cube->screen.mlx)
		exit_program(cube, EXIT_FAILURE, MLX_ERROR);
	cube->screen.win = mlx_new_window(cube->screen.mlx, cube->screen.width, cube->screen.height, \
		"Cub3D");
	if (!cube->screen.win)
		exit_program(cube, EXIT_FAILURE, MLX_WIN_ERROR);
	cube->screen.img.img = mlx_new_image(cube->screen.mlx, cube->screen.width, cube->screen.height);
	if (!cube->screen.img.img)
		exit_program(cube, EXIT_FAILURE, MLX_IMG_ERROR);
	cube->screen.img.addr = mlx_get_data_addr(cube->screen.img.img, &cube->screen.img.bpp, \
		&cube->screen.img.line_length, &cube->screen.img.endian);
	XCloseDisplay(display);
}

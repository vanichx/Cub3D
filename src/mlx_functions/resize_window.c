/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:38:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/09 09:41:37 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void destroy_window(t_cube *cube) {
    if (cube->screen.img.img) {
        mlx_destroy_image(cube->screen.mlx, cube->screen.img.img);
        cube->screen.img.img = NULL;
    }
    if (cube->screen.win) {
        mlx_destroy_window(cube->screen.mlx, cube->screen.win);
        cube->screen.win = NULL;
    }
}

static void update_dimensions(t_cube *cub, int flag)
{
	if (flag == EXPAND)
	{
		if (cub->screen.height > cub->screen.default_h - 1 
			|| cub->screen.width > cub->screen.default_w - 1)
			return ;
		cub->screen.width *= 2;
		cub->screen.height *= 2;
	}
	else if (flag == REDUCE) 
	{
		if (cub->screen.height < 355 || cub->screen.width < 641)
			return ;
		cub->screen.width /= 2;
		cub->screen.height /= 2;
	}
}

static void init_new_window(t_cube *cube) {
	destroy_window(cube);
    // Create a new window
    cube->screen.win = mlx_new_window(cube->screen.mlx, cube->screen.width, cube->screen.height, "Cub3D");
    if (!cube->screen.win)
        exit_program(cube, EXIT_FAILURE, MLX_WIN_ERROR);

    // Allocate memory for a new image
    cube->screen.img.img = mlx_new_image(cube->screen.mlx, cube->screen.width, cube->screen.height);
    if (!cube->screen.img.img)
        exit_program(cube, EXIT_FAILURE, MLX_IMG_ERROR);

    // Get address info for the image
    cube->screen.img.addr = mlx_get_data_addr(cube->screen.img.img, &cube->screen.img.bpp, &cube->screen.img.line_length, &cube->screen.img.endian);
}

// static void hook_events(t_cube *cub)
// {
// 	mlx_hook(cub->screen.win, 2, 0, key_press, cub);
// 	mlx_loop_hook(cub->screen.mlx, render, cub);
// }

void resize_window(t_cube *cub, int flag) {
    update_dimensions(cub, flag);
    destroy_window(cub); // Destroy the old window before creating a new one
    init_new_window(cub);
    hooking(cub);
}

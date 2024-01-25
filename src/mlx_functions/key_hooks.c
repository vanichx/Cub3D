/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:37 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/25 15:48:14 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void increase_player_speed(t_cube *cube)
{
	cube->player.player_speed++;
	cube->player.player_rot_speed += 0.05;
}

void decrease_player_speed(t_cube *cube)
{
	if (cube->player.player_speed > 1)
		cube->player.player_speed--;
	if (cube->player.player_rot_speed > 1)
		cube->player.player_rot_speed -= 0.05;
}


void resize_window(t_cube *cub, int new_width, int new_height)
{
	void *new_mlx;
	void *new_win;

	new_mlx = mlx_init();
	new_win = mlx_new_window(new_mlx, new_width, new_height, "Cub3D");
	mlx_destroy_window(cub->screen.mlx, cub->screen.win);
	
	cub->screen.mlx = new_mlx;
	cub->screen.win = new_win;

	mlx_hook(cub->screen.win, 2, 0, key_press, cub);
	mlx_loop_hook(cub->screen.mlx, render, cub);
}

int key_press(int key, void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	if (key == KEY_ESC)
		cleanup(cub, EXIT_SUCCESS);
	if (key == KEY_W || key == KEY_UP || key == KEY_S || key == KEY_DOWN || key == KEY_D || key == KEY_A)
		//move_player
	if (key == KEY_LEFT || key == KEY_RIGHT) {
		//turn_player
	}
	if (key == KEY_R){
		//rotate "camera"
	}
	if (key == KEY_X && cub->fov > 2)
		cub->fov--;
	if (key == KEY_Z)
		cub->fov++;
	if (key == KEY_SUM || key == KEY_SUM2)
		increase_player_speed(cub);
	if (key == KEY_RES || key == KEY_RES2)
		decrease_player_speed(cub);
	if (key == KEY_I)
	{
		cub->screen.width *= 2;
		cub->screen.height *= 2;
		resize_window(cub, cub->screen.width, cub->screen.height);
	}
	if (key == KEY_U)
	{
		cub->screen.width /= 2;
		cub->screen.height /= 2;
		resize_window(cub, cub->screen.width, cub->screen.height);
	}
	return (EXIT_SUCCESS);
}
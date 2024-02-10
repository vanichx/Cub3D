/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:37 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/10 21:22:44 by segfault         ###   ########.fr       */
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

int key_release(int key, void *param)
{
	t_cube *cub;
	
	cub = (t_cube *)param;
	if (key == KEY_ESC)
		exit_program((t_cube *)param, EXIT_SUCCESS, "Exiting the game\n");
	if (key == KEY_W && cub->player.move[Y] == 1)
		cub->player.move[Y] = 0;
	if (key == KEY_S && cub->player.move[Y] == -1)
		cub->player.move[Y] = 0;
	if (key == KEY_D && cub->player.move[X] == 1)
		cub->player.move[X] -= 1;
	if (key == KEY_A && cub->player.move[X] == -1)
		cub->player.move[Y] += 1;
	if (key == KEY_LEFT && cub->player.rotate <= 1)
		cub->player.rotate = 0;
	if (key == KEY_RIGHT && cub->player.rotate >= -1)
		cub->player.rotate = 0;
	return (EXIT_SUCCESS);
}

int key_press(int key, void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	if (key == KEY_ESC)
		exit_program(cub, EXIT_SUCCESS, "Exiting the game\n");
	if (key == KEY_W)
		cub->player.move[X] = 1;
	if (key == KEY_S)
		cub->player.move[X] = -1;
	if (key == KEY_D)
		cub->player.move[Y] = 1;
	if (key == KEY_A)
		cub->player.move[Y] = -1;
	if (key == KEY_LEFT)
		cub->player.rotate = -1;
	if (key == KEY_RIGHT)
		cub->player.rotate = 1;
	if (key == KEY_R)
	{
		//rotate "camera"
		mlx_put_image_to_window(cub->screen.mlx, cub->screen.win, \
		cub->wall_text.img_text[1].img, 0, 0);
	}
	if (key == KEY_X && cub->player.fov > 2)
		cub->player.fov--;
	if (key == KEY_Z && cub->player.fov < 170)
		cub->player.fov++;
	if (key == KEY_SUM || key == KEY_SUM2)
		increase_player_speed(cub);
	if (key == KEY_RES || key == KEY_RES2)
		decrease_player_speed(cub);
	if (key == KEY_I)
		resize_window(cub, EXPAND);
	if (key == KEY_U)
		resize_window(cub, REDUCE);
	return (EXIT_SUCCESS);
}
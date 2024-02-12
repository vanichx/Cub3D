/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:37 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/12 17:43:54 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void increase_player_speed(t_cube *cube)
// {
// 	printf("increasing player speed: %lf\n", cube->player.player_speed);
// 	cube->player.player_speed++;
// 	cube->player.player_rot_speed += 0.05;
// }

// void decrease_player_speed(t_cube *cube)
// {
// 	printf("decreasing player speed: %lf\n", cube->player.player_speed);
// 	if (cube->player.player_speed > 1)
// 		cube->player.player_speed--;
// 	if (cube->player.player_rot_speed > 1)
// 		cube->player.player_rot_speed -= 0.05;
// }

int key_press(int key, void *param)
{
	printf("key code is %d\n", key);

	t_cube *cube;

	cube = (t_cube *)param;

	if (key == KEY_ESC)
		cube->key.key_esc = 1;
	if (key == KEY_S)
		cube->key.key_s = 1;
	if (key == KEY_W)
		cube->key.key_w = 1;
	if (key == KEY_A)
		cube->key.key_a = 1;
	if (key == KEY_D)
		cube->key.key_d = 1;
	if (key == KEY_LEFT)
        cube->key.key_left = 1;
    if (key == KEY_RIGHT)
        cube->key.key_right = 1;
	if (key == KEY_I)
		resize_window(cube, EXPAND);
	if (key == KEY_U)
		resize_window(cube, REDUCE);
	return (0);
}

int key_release(int key, void *param)
{
	t_cube *cube;
	
	cube = (t_cube *)param;

	if (key == KEY_ESC)
		cube->key.key_esc = 0;
	if (key == KEY_S)
		cube->key.key_s = 0;
	if (key == KEY_W)
		cube->key.key_w = 0;
	if (key == KEY_A)
		cube->key.key_a = 0;
	if (key == KEY_D)
		cube->key.key_d = 0;
	if (key == KEY_LEFT && cube->key.key_left == 1)
	{
		printf("key left released\n");
		cube->key.key_left = 0;
		cube->player.rotate = 0;
	}
	if (key == KEY_RIGHT && cube->key.key_right == 1)
	{
		printf("key right released\n");
		cube->key.key_right = 0;
		cube->player.rotate = 0;
	}
	return (0);
}


int	keys_execute(t_cube *cube)
{	
	if (cube->key.key_esc)
		exit_program(cube, EXIT_SUCCESS, "Exiting the game\n");
	if (cube->key.key_w)
		move_forward(cube);
	if (cube->key.key_s)
		move_backward(cube);
	if (cube->key.key_a)
		move_left(cube);
	if (cube->key.key_d)
		move_right(cube);
	if (cube->key.key_left)
        rotate_left(cube);
    if (cube->key.key_right)
        rotate_right(cube);
	return (0);
}
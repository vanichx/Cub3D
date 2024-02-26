/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:37 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 14:41:14 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	handle_special_keys(int key, t_cube *cube)
{
	if (key == KEY_I)
		resize_window(cube, EXPAND);
	if (key == KEY_U)
		resize_window(cube, REDUCE);
	if (key == KEY_M)
		show_hide_minimap(cube);
	
}

int	key_press(int key, void *param)
{
	t_cube	*cube;

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
	handle_special_keys(key, cube);
	return (0);
}

int	key_release(int key, void *param)
{
	t_cube	*cube;

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
		cube->key.key_left = 0;
	if (key == KEY_RIGHT && cube->key.key_right == 1)
		cube->key.key_right = 0;
	if (key == KEY_2 || key == KEY_1)
	{
		if (key == KEY_1)
			cube->player.info[WEAPON_S] = KNIFE;
		else if (key == KEY_2 && cube->player.info[GUN_LOOT_S])
			cube->player.info[WEAPON_S] = GUN;
		cube->refresh = 1;
	}
	return (0);
}

int mouse_press(int key, void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	if (key == 1)
		cube->key.shoot = 1;
	if (key == 2)
		cube->key.action = 1;
	return (EXIT_SUCCESS);
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

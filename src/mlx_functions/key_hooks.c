/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:37 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/23 12:14:28 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int key_press(int key, void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	if (key == KEY_ESC)
		cleanup(cub);
	if (key == KEY_W || key == KEY_UP || key == KEY_S || key == KEY_DOWN || key == KEY_D || key == KEY_A)
		//move_player
	if (key == KEY_LEFT || key == KEY_RIGHT)
		//turn_player
	if (key == KEY_R)
		//rotate "camera"
	if (key == KEY_X && cub->fov > 2)
		cub->fov--;
	if (key == KEY_Z)
		cub->fov++;
	if (key == KEY_SUM || key == KEY_SUM2)
		//increase player speed
	if (key == KEY_RES || key == KEY_RES2)
		//decrease player speed
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 16:30:03 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left_mouse(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	speed = cube->player.player_rot_speed * 1.5;
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(-speed) - cube->player.front.dir[Y] \
	* sin(-speed);
	cube->player.front.dir[Y] = old_dir_x * sin(-speed) \
	+ cube->player.front.dir[Y] * cos(-speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(-speed) - cube->player.cam.dir[Y] \
	* sin(-speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(-speed) + cube->player.cam.dir[Y] \
	* cos(-speed);
}

void	rotate_right_mouse(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	speed = cube->player.player_rot_speed * 1.5;
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(speed) - cube->player.front.dir[Y] \
	* sin(speed);
	cube->player.front.dir[Y] = old_dir_x \
	* sin(speed) + cube->player.front.dir[Y] \
	* cos(speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(speed) - cube->player.cam.dir[Y] \
	* sin(speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(speed) + cube->player.cam.dir[Y] \
	* cos(speed);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_cube	*cub;

	(void) cub;
	(void) button;
	(void) x;
	(void) y;
	cub = (t_cube *)param;
	return (EXIT_SUCCESS);
}

int	ft_mouse(t_cube *cube)
{
	int	x;
	int	y;
	int	dx;

	mlx_mouse_hide();
	mlx_mouse_get_pos(cube->screen.win, &x, &y);
	dx = x - cube->screen.width / 2;
	if (dx > 2)
		rotate_right_mouse(cube);
	else if (dx < -2)
		rotate_left_mouse(cube);
	mlx_mouse_move(cube->screen.win,
		cube->screen.width / 2, cube->screen.height / 2);
	return (0);
}

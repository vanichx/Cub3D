/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 15:02:09 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] += cube->player.front.dir[X] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] += cube->player.front.dir[Y] \
		* cube->player.player_speed;
}

void	move_backward(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] -= cube->player.front.dir[X] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] -= cube->player.front.dir[Y] \
		* cube->player.player_speed;
}

void	move_left(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] += cube->player.front.dir[Y] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] -= cube->player.front.dir[X] \
		* cube->player.player_speed;
}

void	move_right(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1')
		cube->player.pos[X] -= cube->player.front.dir[Y] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1')
		cube->player.pos[Y] += cube->player.front.dir[X] \
		* cube->player.player_speed;
}

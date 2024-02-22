/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/22 15:30:53 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	ft_mouse(t_cube *cube)
{
	int	x;
	int	y;
	int	dx;

	mlx_mouse_hide();
	mlx_mouse_get_pos(cube->screen.win, &x, &y);
	dx = x - cube->screen.width / 2;
	if (dx > 10)
		rotate_right(cube);
	else if (dx < -10)
		rotate_left(cube);
	mlx_mouse_move(cube->screen.win, cube->screen.width / 2, cube->screen.height / 2);
	return (0);
}
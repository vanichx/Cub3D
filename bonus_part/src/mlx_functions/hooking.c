/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:12 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 14:42:29 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_cube *cube)
{
	exit_program(cube, EXIT_SUCCESS, "Window closed\n");
	return (0);
}

bool	hooking(t_cube *cube)
{
	mlx_hook(cube->screen.win, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->screen.win, 3, 1L << 1, key_release, cube);
	mlx_hook(cube->screen.win, 4, 0, mouse_press, cube);
	mlx_hook(cube->screen.win, 4, 0, mouse_press, cube);
	mlx_hook(cube->screen.win, 5, 0, mouse_release, cube);
	mlx_hook(cube->screen.win, 17, 0, close_window, cube);
	mlx_loop_hook(cube->screen.mlx, render, cube);
	mlx_loop(cube->screen.mlx);
	return (EXIT_SUCCESS);
}

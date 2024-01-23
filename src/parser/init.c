/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:18:59 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/23 12:54:07 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/Xlib.h>
#include "../mlx/mlx.h"

void	init_cube(t_cube *cube)
{
	cube->fov = 60;
	cube->map.map_x = 0;
	cube->map.map_y = 0;
	cube->map.num_line = 0;
	cube->map.num_textures = 0;
	cube->player.pos.x = 0;
	cube->player.pos.y = 0;
	cube->player.player_speed = 10;
	cube->player.player_rot_speed = 4;
	cube->player.move = 0;
	cube->player.rotate = 0;
}

bool	init_window(t_mlx *screen)
{
	Display	*display;
	Screen	*s;

	display = XOpenDisplay(NULL);
	if (!display)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	s = DefaultScreenOfDisplay(display);
	screen->width = s->width / 2;
	screen->height = s->height / 2 ;
	screen->mlx = mlx_init();
	if (!screen->mlx)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	screen->win = mlx_new_window(screen->mlx, screen->width, screen->height, \
		"Cub3D");
	if (!screen->win)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	screen->img = mlx_new_image(screen->mlx, screen->width, screen->height);
	if (!screen->img)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	screen->addr = mlx_get_data_addr(screen->img, &screen->bits_per_pixel, \
		&screen->line_length, &screen->endian);
	XCloseDisplay(display);
	return (EXIT_SUCCESS);
}

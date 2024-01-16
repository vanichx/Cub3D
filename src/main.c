/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 13:32:08 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include "../gnl/get_next_line.h"
#include <errno.h>
#include <X11/Xlib.h>

bool	init_window(t_mlx *screen) {
    Display	*display;
    Screen	*s;

    display = XOpenDisplay(NULL);
    if (!display)
        return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
    s = DefaultScreenOfDisplay(display);

    screen->width = s->width;
    screen->height = s->height;

    screen->mlx = mlx_init();
    if (!screen->mlx)
        return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
    screen->win = mlx_new_window(screen->mlx, screen->width, screen->height, "Cub3D");
    if (!screen->win)
        return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
    screen->img = mlx_new_image(screen->mlx, screen->width, screen->height);
    if (!screen->img)
        return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
    screen->addr = mlx_get_data_addr(screen->img, &screen->bits_per_pixel, &screen->line_length, &screen->endian);

    XCloseDisplay(display);

    return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	bool check;
	t_mlx screen;
	check = init_window(&screen);
	mlx_loop(screen.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:26 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"

#include <X11/Xlib.h>

bool	init_window(t_mlx *screen)
{
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

bool	check_args(int argc, char *argv[])
{
	if (argc != 2)
		return (fprintf(stderr, "❌ Cube error: Wrong number of arguments\n"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (fprintf(stderr, "❌ Cube error: Wrong file extension\n"));
	if (ft_strncmp(argv[1], "maps/", 5))
		return (fprintf(stderr, "❌ Cube error: Wrong file location\n"));
	if (ft_strlen(argv[1]) < 10)
		return (fprintf(stderr, "❌ Cube error: Wrong file naming\n"));
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	t_cube cube;
	
	ft_bzero(&cube, sizeof(t_cube));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (parse_map(argv[1], &cube.map))
		return (EXIT_FAILURE);
	if (init_window(&cube.screen))
		return (EXIT_FAILURE);
	// parsing
	mlx_loop(&cube.screen.mlx);
}

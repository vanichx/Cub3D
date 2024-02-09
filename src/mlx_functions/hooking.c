#include "cub3d.h"

#define WHITE 0xFFFFFF

bool hooking(t_cube *cube)
{
	mlx_hook(cube->screen.win, 2, 1L << 0, key_press, cube);
	// mlx_hook(cube->screen.win, 3, 1L << 1, key_release, cube);
	// mlx_hook(cube->screen.win, 4, 0, mouse_press, cube);
	// mlx_hook(cube->screen.win, 5, 0, mouse_release, cube);
	// mlx_hook(cube->screen.win, 6, 0, mouse_move, cube);
	// mlx_hook(cube->screen.win, 17, 0, cleanup, cube);
	mlx_loop_hook(cube->screen.mlx, render_cube, cube);
	mlx_loop(cube->screen.mlx);
	return (EXIT_SUCCESS);
}

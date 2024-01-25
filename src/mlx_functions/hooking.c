#include "cub3d.h"

#define GREEN 0xFFFFFF

static void	print_results(t_cube *cube, int height, int width)
{
	int		bottom;
	int		mid;



	height = cube->map.map_height;
	width = cube->map.map_width;
	mid = (width * 64 - ((width * 64) / 2));
	bottom = (height * 64 + 15);
	// mlx_put_image_to_window(cube->screen.mlx, cube->screen.win,
	// 	cube->img->bg_count, mid - 150, bottom - 15);
	mlx_string_put(cube->screen.mlx, cube->screen.win,
		mid + 50, bottom, GREEN, "Steps :");
	mlx_string_put(cube->screen.mlx, cube->screen.win,
		mid + 100, bottom, GREEN, "0");
	mlx_string_put(cube->screen.mlx, cube->screen.win,
		mid - 150, bottom, GREEN, "Coins to collect :");
	mlx_string_put(cube->screen.mlx, cube->screen.win,
		mid - 15, bottom, GREEN, "AAAAAAA");
}



int render(t_cube *cube)
{
	


	while (1)
	{
		print_results(cube, cube->map.map_height, cube->map.map_width);
	}
}


bool hooking(t_cube *cube)
{
	mlx_hook(cube->screen.win, 2, 0, key_press, cube);
	// mlx_hook(cube->screen.win, 3, 0, key_release, cube);
	// mlx_hook(cube->screen.win, 4, 0, mouse_press, cube);
	// mlx_hook(cube->screen.win, 5, 0, mouse_release, cube);
	// mlx_hook(cube->screen.win, 6, 0, mouse_move, cube);
	// mlx_hook(cube->screen.win, 17, 0, cleanup, cube);
	// mlx_loop_hook(cube->screen.mlx, render, cube);
	mlx_loop(cube->screen.mlx);
	return (EXIT_SUCCESS);
}

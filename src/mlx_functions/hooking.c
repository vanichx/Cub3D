#include "cub3d.h"

#define WHITE 0xFFFFFF


static void	print_low_bar(t_cube *cube, int height, int width)
{
	int		bottom;
	int		mid;



	height = cube->screen.height;
	width = cube->screen.width;
	mid = width / 2 ;
	bottom = height / 2;
	// mlx_put_image_to_window(cube->screen.mlx, cube->screen.win,
	// 	cube->img->bg_count, mid - 150, bottom - 15);
	mlx_string_put(cube->screen.mlx, cube->screen.win,
		mid + 50, bottom, WHITE, "CUB3D");
	
}



int render(t_cube *cube)
{
	print_low_bar(cube, cube->map.map_height, cube->map.map_width);
}


bool hooking(t_cube *cube)
{
	mlx_hook(cube->screen.win, 2, 0, key_press, cube);
	// mlx_hook(cube->screen.win, 3, 0, key_release, cube);
	// mlx_hook(cube->screen.win, 4, 0, mouse_press, cube);
	// mlx_hook(cube->screen.win, 5, 0, mouse_release, cube);
	// mlx_hook(cube->screen.win, 6, 0, mouse_move, cube);
	// mlx_hook(cube->screen.win, 17, 0, cleanup, cube);
	mlx_loop_hook(cube->screen.mlx, render, cube);
	mlx_loop(cube->screen.mlx);
	return (EXIT_SUCCESS);
}

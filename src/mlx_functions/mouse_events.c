#include "cub3d.h"

/* Handling releasment of mouse*/
int mouse_release(int button, int x, int y, void *param)
{
	t_cube *cub;

	(void) button;
	(void) x;
	(void) y;
	cub = (t_cube *)param;
	return (EXIT_SUCCESS);
}

/* Handling pressment of mouse*/
int mouse_press(int button, int x, int y, void *param)
{
	t_cube *cub;

	(void) button;
	(void) x;
	(void) y;
	cub = (t_cube *)param;
	return (EXIT_SUCCESS);
}

int mouse_move(int x, int y, void *param)
{
	t_cube *cub;
	static t_point old_pos;
	float diff;
	float step;

	cub = (t_cube *)param;
	diff = old_pos.x - x;
	step = diff / 10;
	cub->player.front = rotate_vec(cub->player.front, step);
	cub->player.cam = cub->player.front;
	old_pos.x = x;
	old_pos.y = y;
	return (EXIT_SUCCESS);
}
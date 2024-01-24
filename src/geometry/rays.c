#include "cub3d.h"

#define FOV 60
#define RAY_ANGLE (FOV / cube->screen.width)

void calculate_ray_directions(t_cube *cube)
{
	float ray_angle;

	for (int i = 0; i < cube->screen.width; i++)
	{
		ray_angle = DEG_TO_RAD(cube->player.init_view + cube->player.rotate - (FOV / 2) + (i * RAY_ANGLE));

		cube->player.front.dir[X] = cos(ray_angle);
		cube->player.front.dir[Y] = sin(ray_angle);

		float old_front_x = cube->player.front.dir[X];
		cube->player.front.dir[X] = old_front_x * cos(cube->player.rotate) - cube->player.front.dir[Y] * sin(cube->player.rotate);
		cube->player.front.dir[Y] = old_front_x * sin(cube->player.rotate) + cube->player.front.dir[Y] * cos(cube->player.rotate);

		// Convert the direction vector to an angle for debugging or visualization
		float angle = vec_to_ang(cube->player.front);
		printf("Ray %d Angle: %f\n", i, angle);
	}
}

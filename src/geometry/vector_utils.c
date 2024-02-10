#include <cub3d.h>

float	vec_to_ang(t_vec vec)
{
	double ang;
	ang = atan2(vec.dir[Y], vec.dir[X]) * 180 / M_PI;
	if (ang < 0)
		ang += 360;
	return (ang);
}

double ang_to_rad(double ang)
{
	return (ang * M_PI / 180);
}

t_vec	get_vunit(t_point p1, t_point p2)
{
	t_point point;
	t_vec vec;
	float magnitude;

	point.x = p2.x - p1.x;
	point.y = p2.y - p1.y;
	magnitude = sqrt(point.x * point.x + point.y * point.y);
	vec.dir[X] = point.x / magnitude;
	vec.dir[Y] = point.y / magnitude;
	return (vec);
}


// x' = x * cos(θ) - y * sin(θ)
// y' = x * sin(θ) + y * cos(θ)
// the rotation of a vector is done by multiplying the vector by a rotation matrix
t_vec	get_cam_vec(t_vec front, float fov)
{
	t_vec vec;
	float half_ang;

	half_ang = fov / 2;
	vec.dir[X] = front.dir[X] * cos(half_ang) - front.dir[Y] * sin(half_ang);
	vec.dir[Y] = front.dir[X] * sin(half_ang) + front.dir[Y] * cos(half_ang);
	return (vec);
}

double get_front_length(t_cube *cube)
{
	double front_length;

	front_length = (cube->screen.width / 2) / tan(cube->player.fov / 2);
	return (front_length);
}

void	set_front_cam_vec(char player, t_vec *front, t_vec *cam)
{
	if (player == 'N')
	{
		front->dir[X] = 0;
		front->dir[Y] = -1;
		cam->dir[X] = 0.66;
		cam->dir[Y] = 0;
 	}
	if (player == 'S')
	{
		front->dir[X] = 0;
		front->dir[Y] = 1;
		cam->dir[X] = -0.66;
		cam->dir[Y] = 0;
	}
	if (player == 'E')
	{
		front->dir[X] = 1;
		front->dir[Y] = 0;
		cam->dir[X] = 0;
		cam->dir[Y] = -0.66;
	}
	if (player == 'W')
	{
		front->dir[X] = -1;
		front->dir[Y] = 0;
		cam->dir[X] = 0;
		cam->dir[Y] = 0.66;
	}
}

t_vec rotate_vec(t_vec vec, float ang)
{
    t_vec new_vec;
    float rad;

    rad = ang * M_PI / 180;
    new_vec.dir[X] = vec.dir[X] * cos(rad) - vec.dir[Y] * sin(rad);
    new_vec.dir[Y] = vec.dir[X] * sin(rad) + vec.dir[Y] * cos(rad);
    return new_vec;
}

// normalise the x and y components of the vector between [-1, 1] and return the vector
t_vec find_casting_vec(t_cube *cube, int x)
{
	double camera_x;
	t_vec ray;

	camera_x = 2 * x / (double)cube->screen.width - 1;
	ray.dir[X] = cube->player.front.dir[X] + cube->player.cam.dir[X] * camera_x;
	ray.dir[Y] = cube->player.front.dir[Y] + cube->player.cam.dir[Y] * camera_x;
	return (ray);
}


/** 
 * This functions ensure that the magnitude of the vec is 1,so it only represents
 *  the direction of the vec. It is used to calculate the direction of the player
 *  and the camera. Returns the normalized vec.
*/
t_vec	normalize_vec(t_vec vec)
{
	float magnitude;

	magnitude = sqrt(vec.dir[X] * vec.dir[X] + vec.dir[Y] * vec.dir[Y]);
	vec.dir[X] /= magnitude;
	vec.dir[Y] /= magnitude;
	return (vec);
}

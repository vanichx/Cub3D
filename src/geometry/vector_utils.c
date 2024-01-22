#include "structures.h"
#include "math.h"

float	vec_to_ang(t_vec vec)
{
	double ang;
	ang = atan2(vec.dir[Y], vec.dir[X]) * 180 / M_PI;
	if (ang < 0)
		ang += 360;
	return (ang);
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

t_vec	get_dir_vec(char dir)
{
	t_vec vec;

	if (dir == 'N')
	{
		vec.dir[X] = 0;
		vec.dir[Y] = -1;
 	}
	if (dir == 'S')
	{
		vec.dir[X] = 0;
		vec.dir[Y] = 1;
	}
	if (dir == 'E')
	{
		vec.dir[X] = 1;
		vec.dir[Y] = 0;
	}
	if (dir == 'W')
	{
		vec.dir[X] = -1;
		vec.dir[Y] = 0;
	}
	return (vec);
}

t_vec	rotate_vec(t_vec vec, float ang)
{
	t_vec new_vec;
	float rad;

	rad = ang * M_PI / 180;
	new_vec.dir[X] = vec.dir[X] * cos(rad) - vec.dir[Y] * sin(rad);
	new_vec.dir[Y] = vec.dir[X] * sin(rad) + vec.dir[Y] * cos(rad);
	return (vec);
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

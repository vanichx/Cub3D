#ifndef GEO_H
#define GEO_H

#include "cub3d.h"

/* vector_utils.c */
float	vec_to_ang(t_vec vec);
t_vec	get_vunit(t_point p1, t_point p2);
t_vec	get_dir_vec(char dir);
t_vec	rotate_vec(t_vec vec, float ang);
t_vec	normalize_vec(t_vec vec);

/* rays.c */
void	calculate_ray_directions(t_cube *cube);

#endif
#ifndef GEO_H
#define GEO_H

#include "cub3d.h"

/* vector_utils.c */
float	vec_to_ang(t_vec vec);
double    ang_to_rad(double ang);
t_vec	get_vunit(t_point p1, t_point p2);
t_vec	get_dir_vec(char dir);
t_vec	rotate_vec(t_vec vec, float ang);
t_vec	normalize_vec(t_vec vec);
t_vec	get_cam_vec(t_vec front);
double get_front_length(t_cube *cube);
t_vec find_casting_vec(t_cube *cube, int x);

/* rays.c */
void prepare_DDA(t_cube *cube, t_vec ray_dir, int step[2], double sideDist[2]);
void    performRaycasting(t_cube *cube);
int cast_ray(t_cube *cube, t_vec ray_dir);

#endif
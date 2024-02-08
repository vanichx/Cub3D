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
t_vec	get_cam_vec(t_vec front, float fov);
double get_front_length(t_cube *cube);
t_vec find_casting_vec(t_cube *cube, int x);

/* render */
int render_cube(t_cube *cube);

/* rays.c */
int render_cube(t_cube *cube);

/* raycasting.c */
void    realloc_text_pixels(int *(*text_pixels)[4], t_cube *cube);
void    setup_dda_params(t_cube *cube, t_ray *ray);
void    perform_dda(t_cube *cube, t_ray *ray);
void    update_texts_pixels(t_cube *cube, t_ray *ray, int x);
void    raycast(t_cube *cube, t_ray *ray);

#endif
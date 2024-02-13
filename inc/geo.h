/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:11 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 16:25:04 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_H
# define GEO_H

# include "cub3d.h"

/* vector_utils.c */
float	vec_to_ang(t_vec vec);
double	ang_to_rad(double ang);
t_vec	get_vunit(t_point p1, t_point p2);
void	set_fr_cam_v(char player, t_vec *front, t_vec *cam);
t_vec	rotate_vec(t_vec vec, float ang);
t_vec	normalize_vec(t_vec vec);
t_vec	get_cam_vec(t_vec front, float fov);
double	get_front_length(t_cube *cube);
t_vec	find_casting_vec(t_cube *cube, int x);

/* render */
int		render_cube(t_cube *cube);
void	render_frame(t_cube *cube);
void	set_frame_image_pixel(t_cube *cube, t_img *img, int i[2]);
void	set_image_pixel(t_img *img, int i[2], int color);
int render(t_cube *cube);

/* rays.c */
void	init_ray(t_ray *ray);
void	setup_ray_params(t_cube *cube, t_ray *ray, int x);
void	calculate_line_height(t_cube *cube, t_ray *ray);
int		get_texture_index(t_ray *ray);

/* raycasting.c */
void	setup_dda_params(t_cube *cube, t_ray *ray);
void	perform_dda(t_cube *cube, t_ray *ray);
void	update_texts_pixels(t_cube *cube, t_ray *ray, int x);
void	raycast(t_cube *cube, t_ray *ray);



#endif
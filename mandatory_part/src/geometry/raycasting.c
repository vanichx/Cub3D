/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:37:00 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/15 16:23:11 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_dda_params(t_cube *cube, t_ray *ray)
{
	if (ray->ray_dir.dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (cube->player.pos[X] - ray->map_point[X]) \
		* ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (ray->map_point[X] + 1.0 - cube->player.pos[X]) \
		* ray->delta_dist[X];
	}
	if (ray->ray_dir.dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (cube->player.pos[Y] - ray->map_point[Y]) \
		* ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (ray->map_point[Y] + 1.0 - cube->player.pos[Y]) \
		* ray->delta_dist[Y];
	}
}

void	perform_dda(t_cube *cube, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map_point[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map_point[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (cube->map.map[(int)ray->map_point[Y]]
			[(int)ray->map_point[X]] == '1')
			hit = 1;
	}
}

float calculate_shadow_intensity(float wall_dist, float max_distance) {
    float shadow_intensity;
	
	shadow_intensity = 1.0 - (wall_dist / max_distance);
    shadow_intensity = fmaxf(0.0, fminf(1.0, shadow_intensity));
    return (shadow_intensity);
}

int apply_shadow(int color, float shadow_intensity) {
    int red;
    int green;
    int blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
    red = (int)(red * shadow_intensity);
    green = (int)(green * shadow_intensity);
    blue = (int)(blue * shadow_intensity);
    return ((red << 16) | (green << 8) | blue);
}

void	update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
	int	y;
	int	color;
	int	texture_index;
	float shadow_intesity;

	texture_index = get_texture_index(ray);
	cube->wall_text.text_point[X] = (int)(ray->wall_x \
	* cube->wall_text.tex_size);
	shadow_intesity = calculate_shadow_intensity(ray->wall_dist, 17);
	if (((ray->side == 0) && (ray->ray_dir.dir[X] < 0))
		|| ((ray->side == 1) && (ray->ray_dir.dir[Y] > 0)))
		cube->wall_text.text_point[X] = cube->wall_text.tex_size \
		- cube->wall_text.text_point[X] - 1;
	cube->wall_text.tex_step = 1.0 * cube->wall_text.tex_size \
	/ ray->line_height;
	cube->wall_text.tex_pos = (ray->draw[START] - cube->screen.height \
	/ 2 + ray->line_height / 2) * cube->wall_text.tex_step;
	y = ray->draw[START];
	while (y < ray->draw[END])
	{
		cube->wall_text.text_point[Y] = (int)cube->wall_text.tex_pos \
		& (cube->wall_text.tex_size - 1);
		cube->wall_text.tex_pos += cube->wall_text.tex_step;
		color = cube->wall_text.textures[texture_index]
		[cube->wall_text.tex_size * cube->wall_text.text_point[Y] \
		+ cube->wall_text.text_point[X]];
		if (texture_index == NO || texture_index == EA)
			color = (color >> 1) & 8355711;
		color = apply_shadow(color, shadow_intesity);
		if (color > 0)
			cube->wall_text.text_pixels[y][x] = color;
		y++;
	}
}

void	raycast(t_cube *cube, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < cube->screen.width)
	{
		setup_ray_params(cube, ray, x);
		setup_dda_params(cube, ray);
		perform_dda(cube, ray);
		calculate_line_height(cube, ray);
		update_texts_pixels(cube, ray, x);
		x++;
	}
	render_frame(cube);
}

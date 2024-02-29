/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:52:03 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 10:22:08 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_left_right_rays(t_cube *c)
{
	c->player.ray.ray_dir_l.dir[X] = c->player.front.dir[X]
		- c->player.cam.dir[X];
	c->player.ray.ray_dir_l.dir[Y] = c->player.front.dir[Y]
		- c->player.cam.dir[Y];
	c->player.ray.ray_dir_r.dir[X] = c->player.front.dir[X]
		+ c->player.cam.dir[X];
	c->player.ray.ray_dir_r.dir[Y] = c->player.front.dir[Y]
		+ c->player.cam.dir[Y];
}

void	cast_floor(t_cube *c, int y)
{
	int		p;
	double	pos_z;
	double	row_distance;
	double	floor_step[2];
	double	floor[2];
	int		x;
	int		cell[2];
	int		t[2];

	x = 0;
	update_left_right_rays(c);
	p = y - c->screen.height / 2;
	pos_z = 0.5 * c->screen.height;
	row_distance = pos_z / p;
	floor_step[X] = row_distance * (c->player.ray.ray_dir_r.dir[X] - c->player.ray.ray_dir_l.dir[X]) / c->screen.width;
	floor_step[Y] = row_distance * (c->player.ray.ray_dir_r.dir[Y] - c->player.ray.ray_dir_l.dir[Y]) / c->screen.width;
	floor[X] = c->player.pos[X] + row_distance * c->player.ray.ray_dir_l.dir[X];
	floor[Y] = c->player.pos[Y] + row_distance * c->player.ray.ray_dir_l.dir[Y];
	while (x < c->screen.width)
	{
		cell[X] = (int)(floor[X]);
		cell[Y] = (int)(floor[Y]);
		t[X] = (int)(c->wall_text.tex_size * (floor[X] - cell[X])) & (c->wall_text.tex_size - 1);
		t[Y] = (int)(c->wall_text.tex_size * (floor[Y] - cell[Y])) & (c->wall_text.tex_size - 1);
		floor[X] += floor_step[X];
		floor[Y] += floor_step[Y];
		c->text_pixels[y][x] = (c->wall_text.textures[F][c->wall_text.tex_size * t[Y] + t[X]] >> 1) & 8355711;
		c->text_pixels[c->screen.height - y - 1][x] = (c->wall_text.textures[C][c->wall_text.tex_size * t[Y] + t[X]] >> 1) & 8355711;
		x++;
	}
}

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
		if (cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '1'
			|| cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '2')
		{
			if (cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '2')
				ray->hit_door = 1;
			hit = 1;
		}
	}
}

void	update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
	int		y;
	int		color;
	int		texture_index;

	texture_index = get_texture_index(ray);
	cube->wall_text.text_point[X] = (int)(ray->wall_x \
	* (double)TEXT_SIZE);
	if (((ray->side == X) && (ray->ray_dir.dir[X] > 0))
		|| ((ray->side == Y) && (ray->ray_dir.dir[Y] < 0)))
		cube->wall_text.text_point[X] = TEXT_SIZE \
		- cube->wall_text.text_point[X] - 1;
	cube->wall_text.tex_step = 1.0 * TEXT_SIZE \
	/ ray->line_height;
	cube->wall_text.tex_pos = (ray->draw[START] - cube->screen.height \
	/ 2 + ray->line_height / 2) * cube->wall_text.tex_step;
	y = ray->draw[START];
	while (y < ray->draw[END])
	{
		cube->wall_text.text_point[Y] = (int)cube->wall_text.tex_pos \
		& (TEXT_SIZE - 1);
		cube->wall_text.tex_pos += cube->wall_text.tex_step;
		color = cube->wall_text.textures[texture_index]
		[TEXT_SIZE * cube->wall_text.text_point[Y] \
		+ cube->wall_text.text_point[X]];
		if (ray->side == Y)
			color = (color >> 1) & 8355711;
		cube->text_pixels[y][x] = color;
		y++;
	}
}

void	render_game_over(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (i < cube->screen.height)
	{
		j = 0;
		while (j < cube->screen.width)
		{
			cube->text_pixels[i][j] = 0x00FF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, cube->screen.img.img, 0, 0);
	mlx_string_put(cube->screen.mlx, cube->screen.win, cube->screen.width / 2 - 100, cube->screen.height / 2, 0x00FF0000, "GAME OVER!");
}

void	render_win_screen(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (i < cube->screen.height)
	{
		j = 0;
		while (j < cube->screen.width)
		{
			cube->text_pixels[i][j] = 0x00FF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, cube->screen.img.img, 0, 0);
	mlx_string_put(cube->screen.mlx, cube->screen.win, cube->screen.width / 2 - 100, cube->screen.height / 2, 0x00FF0000, "YOU WIN!");
}

void	raycast_bonus(t_cube *cube, t_ray *ray)
{
    int	x;
    int	y;
	double z_buffer[cube->screen.width];

    x = -1;
    y = -1;
	if (cube->game_status == 1)
		render_game_over(cube);
	else if (cube->game_status == 2)
		render_win_screen(cube);
	else
	{
		while (++y < cube->screen.height)
			cast_floor(cube, y);
		while (++x < cube->screen.width)
		{
			setup_ray_params(cube, ray, x);
			setup_dda_params(cube, ray);
			perform_dda(cube, ray);
			calculate_line_height(cube, ray);
			if (ray->hit_door == 1)
				draw_door(cube, ray, x);
			else
				update_texts_pixels(cube, ray, x);
			z_buffer[x] = ray->wall_dist;
		}
		if ((int)cube->player.pos[X] == (int)cube->sprite.sprite_text[KEY].text_point[X] && (int)cube->player.pos[Y] == (int)cube->sprite.sprite_text[KEY].text_point[Y])
			cube->key_status = 1;
		cast_sprites(cube, z_buffer);
		render_frame(cube);
	}
}

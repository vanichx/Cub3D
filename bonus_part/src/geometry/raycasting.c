#include "cub3d.h"

void update_left_right_rays(t_cube *c)
{
	c->player.ray.ray_dir_l.dir[X] = c->player.front.dir[X] - c->player.cam.dir[X];
	c->player.ray.ray_dir_l.dir[Y] = c->player.front.dir[Y] - c->player.cam.dir[Y];
	c->player.ray.ray_dir_r.dir[X] = c->player.front.dir[X] + c->player.cam.dir[X];
	c->player.ray.ray_dir_r.dir[Y] = c->player.front.dir[Y] + c->player.cam.dir[Y];
}

void cast_floor(t_cube *c, int y)
{
	int p;
	float pos_z;
	float row_distance;
	float floor_step[2];
	float floor[2];
	int x;
	int cell[2];
	int t[2];

	x = 0;
	update_left_right_rays(c);
	p = y - c->screen.height / 2;  // current y position compared to the center of the screen
	pos_z = 0.5 * c->screen.height; // vertical position of the camera
	row_distance = pos_z / p;
	floor_step[X] = row_distance * (c->player.ray.ray_dir_r.dir[X] - c->player.ray.ray_dir_l.dir[X]) / c->screen.width;
	floor_step[Y] = row_distance * (c->player.ray.ray_dir_r.dir[Y] - c->player.ray.ray_dir_l.dir[Y]) / c->screen.width;
	floor[X] = c->player.pos[X] + row_distance * c->player.ray.ray_dir_r.dir[X];
	floor[Y] = c->player.pos[Y] + row_distance * c->player.ray.ray_dir_r.dir[Y];
	while (x < c->screen.width)
	{
		cell[X] = (int)(floor[X]);
		cell[Y] = (int)(floor[Y]);
		t[X] = (int)(c->wall_text.tex_size * (floor[X] - cell[X])) & (c->wall_text.tex_size - 1);
		t[Y] = (int)(c->wall_text.tex_size * (floor[Y] - cell[Y])) & (c->wall_text.tex_size - 1);
		floor[X] += floor_step[X];
		floor[Y] += floor_step[Y];
		c->wall_text.text_pixels[y][x] = (c->wall_text.textures[F][c->wall_text.tex_size * t[Y] + t[X]] >> 1) & 8355711;
		c->wall_text.text_pixels[c->screen.height - y - 1][x] = c->wall_text.textures[C][c->wall_text.tex_size * t[Y] + t[X]];
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
		if (cube->map.map[(int)ray->map_point[Y]]
			[(int)ray->map_point[X]] == '1')
			hit = 1;
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
		cube->wall_text.text_pixels[y][x] = color;
		y++;
	}
}

void	raycast_bonus(t_cube *cube, t_ray *ray)
{
	int	x;
	int y;

	x = -1;
	y = -1;
	while (++y < cube->screen.height)
		cast_floor(cube, y);
	while (++x < cube->screen.width)
	{
		setup_ray_params(cube, ray, x);
		setup_dda_params(cube, ray);
		perform_dda(cube, ray);
		calculate_line_height(cube, ray);
		update_texts_pixels(cube, ray, x);
	}
	render_frame(cube);
}

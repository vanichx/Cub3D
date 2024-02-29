/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:21:32 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 13:20:30 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_door(t_cube *cube, t_ray *ray, int x)
{
    int		y;
    int		color;

    cube->sprite.sprite_text[DOOR].text_point[X] = (int)(ray->wall_x \
    * (double)TEXT_SIZE);
    if (((ray->side == X) && (ray->ray_dir.dir[X] > 0))
        || ((ray->side == Y) && (ray->ray_dir.dir[Y] < 0)))
        cube->sprite.sprite_text[DOOR].text_point[X] = TEXT_SIZE \
        - cube->sprite.sprite_text[DOOR].text_point[X] - 1;
    cube->sprite.sprite_text[DOOR].tex_step = 1.0 * TEXT_SIZE \
    / ray->line_height;
    cube->sprite.sprite_text[DOOR].tex_pos = (ray->draw[START] - cube->screen.height \
    / 2 + ray->line_height / 2) * cube->sprite.sprite_text[DOOR].tex_step;
    y = ray->draw[START];
    while (y < ray->draw[END])
    {
        cube->sprite.sprite_text[DOOR].text_point[Y] = (int)cube->sprite.sprite_text[DOOR].tex_pos \
        & (TEXT_SIZE - 1);
        cube->sprite.sprite_text[DOOR].tex_pos += cube->sprite.sprite_text[DOOR].tex_step;
        color = cube->sprite.sprite_text[DOOR].pixels
        [TEXT_SIZE * (int)cube->sprite.sprite_text[DOOR].text_point[Y] \
        + (int)cube->sprite.sprite_text[DOOR].text_point[X]];
        if (ray->side == Y)
            color = (color >> 1) & 8355711;
        cube->text_pixels[y][x] = color;
		if (cube->door == 1)
			cube->text_pixels[y][x] = 0x00FF0000;
        y++;
    }
}

void sort_sprites(t_sprite *sprite, t_cube *cube)
{
	int i;
	int temp_order;
	double temp_distance;

	i = ENEMY;
	while (i < DOOR)
	{
		sprite->sprite_order[i] = i;
        sprite->sprite_dist[i] = ((cube->player.pos[X] - cube->sprite.sprite_text[i].text_pos[X]) \
		* (cube->player.pos[X] - cube->sprite.sprite_text[i].text_pos[X]) + (cube->player.pos[Y] \
		- cube->sprite.sprite_text[i].text_pos[Y]) * (cube->player.pos[Y] - \
		cube->sprite.sprite_text[i].text_pos[Y]));
		i++;
	}
	if (sprite->sprite_dist[ENEMY] > sprite->sprite_dist[KEY])
	    return ;
	else
	{
		temp_order = sprite->sprite_order[ENEMY];
		sprite->sprite_order[ENEMY] = sprite->sprite_order[KEY];
		sprite->sprite_order[KEY] = temp_order;
		temp_distance = sprite->sprite_dist[ENEMY];
		sprite->sprite_dist[ENEMY] = sprite->sprite_dist[KEY];
		sprite->sprite_dist[KEY] = temp_distance;
	}
}

void set_sprite_text(t_sprite *sprite, t_cube *cube, int i)
{
	sprite->sprite_text[i].text_pos[X] = sprite->sprite_text[i].text_point[X] - cube->player.pos[X];
	sprite->sprite_text[i].text_pos[Y] = sprite->sprite_text[i].text_point[Y] - cube->player.pos[Y];
	sprite->sprite_text[i].inv_det = 1.0 / (cube->player.cam.dir[X] * cube->player.front.dir[Y] - cube->player.front.dir[X] * cube->player.cam.dir[Y]);
	sprite->sprite_text[i].transform[X] = sprite->sprite_text[i].inv_det * (cube->player.front.dir[Y] * sprite->sprite_text[i].text_pos[X] - cube->player.front.dir[X] * sprite->sprite_text[i].text_pos[Y]);
	sprite->sprite_text[i].transform[Y] = sprite->sprite_text[i].inv_det * (-cube->player.cam.dir[Y] * sprite->sprite_text[i].text_pos[X] + cube->player.cam.dir[X] * sprite->sprite_text[i].text_pos[Y]);
	sprite->sprite_text[i].screen_x = (int)((cube->screen.width / 2) * (1 + sprite->sprite_text[i].transform[X] / sprite->sprite_text[i].transform[Y]));
	sprite->sprite_text[i].h = abs((int)(cube->screen.height / (sprite->sprite_text[i].transform[Y])));
	sprite->sprite_text[i].start[Y] = -sprite->sprite_text[i].h / 2 + cube->screen.height / 2;
	if(sprite->sprite_text[i].start[Y] < 0)
		sprite->sprite_text[i].start[Y] = 0;
	sprite->sprite_text[i].end[Y] = sprite->sprite_text[i].h / 2 + cube->screen.height / 2;
	if(sprite->sprite_text[i].end[Y] >= cube->screen.height)
		sprite->sprite_text[i].end[Y] = cube->screen.height - 1;
	sprite->sprite_text[i].w = abs((int)(cube->screen.height / (sprite->sprite_text[i].transform[Y])));
	sprite->sprite_text[i].start[X] = -sprite->sprite_text[i].w / 2 + sprite->sprite_text[i].screen_x;
	if(sprite->sprite_text[i].start[X] < 0)
		sprite->sprite_text[i].start[X] = 0;
	sprite->sprite_text[i].end[X] = sprite->sprite_text[i].w / 2 + sprite->sprite_text[i].screen_x;
	if(sprite->sprite_text[i].end[X] >= cube->screen.width)
		sprite->sprite_text[i].end[X] = cube->screen.width - 1;
}

void move_enemy(int map_height, int map_width, char **map, double *enemy_x, double *enemy_y, t_cube *cube)
{
    const int movement_interval = 7;
    static int iteration_count = 0;
	enum Direction direction;
	double new[2];

	if (iteration_count < 100)
    	iteration_count++;
	else if (iteration_count == 100)
		iteration_count = 0;
    if (iteration_count % movement_interval != 0)
        return;
    direction = rand() % 4;
    new[X] = (*enemy_x);
    new[Y] = (*enemy_y);
	if (direction == UP)
		new[Y] -= 0.5;
	else if (direction == DOWN)
		new[Y] += 0.5;
	else if (direction == LEFT)
		new[X] -= 0.5;
	else if (direction == RIGHT)
		new[X] += 0.5;
    if (new[X] >= 0 && new[X] < map_width && new[Y] >= 0 && new[Y] < map_height && map[(int)new[Y]][(int)new[X]] != '1' && map[(int)new[Y]][(int)new[X]] != '2')
	{
		if (map[(int)(new[Y] + 1)][(int)new[X]] == '1')
			new[Y] -= 0.5;
		if (map[(int)(new[Y] - 1)][(int)new[X]] == '1')
			new[Y] += 0.5;
		if (map[(int)new[Y]][(int)(new[X] + 1)] == '1')
			new[X] -= 0.5;
		if (map[(int)new[Y]][(int)(new[X] - 1)] == '1')
			new[X] += 0.5;
        *enemy_x = new[X];
        *enemy_y = new[Y];
		if ((int)*enemy_x == (int)cube->player.pos[X] && (int)*enemy_y == (int)cube->player.pos[Y])
			cube->game_status = 1;
    }
}


void cast_sprites(t_cube *cube, double *z_buffer)
{
	int i[2];
	int stripe;
	int tex[2];
	t_sprite_tex sprite_text;

	i[X] = 0;
	move_enemy(cube->map.map_height, cube->map.map_width, cube->map.map, &cube->sprite.sprite_text[ENEMY].text_point[X], &cube->sprite.sprite_text[ENEMY].text_point[Y], cube);
	sort_sprites(&cube->sprite, cube);
	while (i[X] < 2)
    {
		if (i[X] == KEY && cube->key_status == 1)
		{
			i[X]++;
			continue ;
		}
		set_sprite_text(&cube->sprite, cube, cube->sprite.sprite_order[i[X]]);
		sprite_text = cube->sprite.sprite_text[cube->sprite.sprite_order[i[X]]];
		stripe = sprite_text.start[X];
		while (stripe < sprite_text.end[X])
        {
			tex[X] = (int)(256 * (stripe - (-sprite_text.w / 2 + sprite_text.screen_x)) * TEXT_SIZE / sprite_text.w) / 256;
			if (sprite_text.transform[Y] > 0 && stripe > 0 && stripe < cube->screen.width && sprite_text.transform[Y] < z_buffer[stripe])
			{
				i[Y] = sprite_text.start[Y];
				while (i[Y] < sprite_text.end[Y])
				{
					sprite_text.d = (i[Y]) * 256 - cube->screen.height * 128 + sprite_text.h * 128;
					tex[Y] = ((sprite_text.d * TEXT_SIZE) / sprite_text.h) / 256;
					sprite_text.color = sprite_text.pixels[TEXT_SIZE * tex[Y] + tex[X]];
					if ((sprite_text.color & 0x00FFFFFF) != 0)
						cube->text_pixels[i[Y]][stripe] = sprite_text.color;
					i[Y]++;
				}
			}
			stripe++;
        }
		i[X]++;
    }
}
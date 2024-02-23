/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:30:03 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/23 13:15:10 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_cube *cube, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(cube->screen.mlx, width, height);
	if (image->img == NULL)
		exit_program(cube, 1, "Error: mlx_new_image failed");
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
		&image->line_length, &image->endian);
	return ;
}

void	render_minimap_image(t_cube *cube, t_minimap *minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE + minimap->tile_size;
	init_img(cube, &cube->minimap, img_size, img_size);
	draw_minimap(minimap);
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, cube->minimap.img,
		10, cube->screen.height
		- (MMAP_PIXEL_SIZE + 30));
	mlx_destroy_image(cube->screen.mlx, cube->minimap.img);
}


void mm_set_image_pixel(t_img *image, int x, int y, int color)
{
	int pixel;

	pixel = y * image->line_length + x * (image->bpp / 8);
	printf("pixel: %d\n", pixel);
	image->addr[pixel + 0] = (color >>  0) & 0xFF;
	image->addr[pixel + 1] = (color >>  8) & 0xFF;
	image->addr[pixel + 2] = (color >> 16) & 0xFF;
	image->addr[pixel + 3] = (color >> 24) & 0xFF;
}

void	set_minimap_tile_pixels(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;

	
	while (i <= minimap->tile_size)
	{
		j = 0;
		while (j <= minimap->tile_size)
		{
			mm_set_image_pixel(minimap->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{

	if (minimap->map[y][x] == 'N' || minimap->map[y][x] == 'S'
		|| minimap->map[y][x] == 'E' || minimap->map[y][x] == 'W')
	{
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x00FF00);
	}
	else if (minimap->map[y][x] == '1') {

		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x606060);
	}
	else if (minimap->map[y][x] == '0') {

		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x80E0E0E0);
	}
	else if (minimap->map[y][x] == ' ')
		{
			set_minimap_tile_pixels(minimap, x * minimap->tile_size,
				y * minimap->tile_size, 0x404040);
		}
}

void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 3 || x > size - 3 || y < 3 || y > size - 3)
				mm_set_image_pixel(minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y] || !minimap->map[y][x]
				|| minimap->map[y][x] == '\0')
				break ;
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border_image_pixels(minimap, 0x000000);
}



bool	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (true);
	return (false);
}

char	*add_minimap_line(t_cube *d, t_minimap *m, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(m->size + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < m->size && x < d->map.map_width)
	{
		if (!is_valid_map_coord(y + m->offset_y, d->map.map_height) 
			|| !is_valid_map_coord(x + m->offset_x, d->map.map_width)) 
				line[x] = '\0';
		else if ((int)d->player.m_pos.x == (x + m->offset_x) 
			&& (int)d->player.m_pos.y == (y + m->offset_y))
				line[x] = 'N';
		else if (d->map.map[y + m->offset_y][x + m->offset_x] == '1')
			line[x] = '1';
		else if (d->map.map[y + m->offset_y][x + m->offset_x] == 'F')
			line[x] = '0';
		else if (d->map.map[y + m->offset_y][x + m->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

char	**generate_minimap(t_cube *cube, t_minimap *minimap)
{
	char	**mmap;
	int		y;

	mmap = ft_calloc(minimap->size + 1, sizeof * mmap);
	if (!mmap)
		return (NULL);
	y = 0;
	while (y < minimap->size && y < cube->map.map_height)
	{
		mmap[y] = add_minimap_line(cube, minimap, y);
		if (!mmap[y])
		{
			free_tab((void **)mmap);
			return (NULL);
		}
		y++;
	}
	return (mmap);
}

int	get_mmap_offset(t_minimap *minimap, int size, int p_pos)
{
	if (p_pos > minimap->view_dist && size - p_pos > (minimap->view_dist + 1))
		return (p_pos - minimap->view_dist);
	if (p_pos > minimap->view_dist && size - p_pos <= (minimap->view_dist + 1))
		return (size - minimap->size);
	return (0);
}

bool	is_valid_pos_wall_collision(t_cube *cube, double x, double y)
{
	if (cube->map.map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

void	update_player_position(t_cube *cube)
{
	float	new_x;
	float	new_y;

	new_x = cube->player.pos[X] + cube->player.front.dir[X]
		* cube->player.player_speed * 2;
	new_y = cube->player.pos[Y] + cube->player.front.dir[Y]
		* cube->player.player_speed * 2;
	if (is_valid_pos_wall_collision(cube, new_x, new_y) == true)
	{
		cube->player.m_pos.x = new_x;
		cube->player.m_pos.y = new_y;
	}
}

void	calculate_minimap_offset(t_minimap *minimap, t_cube *cube)
{
	if ((int)cube->player.pos[X] >= cube->map.map_width - 3
		|| (int)cube->player.pos[X] >= cube->map.map_width - 4
		|| (int)cube->player.pos[X] >= cube->map.map_width - 5)
		minimap->offset_x = get_mmap_offset(minimap, cube->map.map_width,
				(int)cube->player.pos[X]) - 1;
	else
		minimap->offset_x = get_mmap_offset(minimap, cube->map.map_width,
				(int)cube->player.pos[X]);
	minimap->offset_y = get_mmap_offset(minimap, cube->map.map_height,
			(int)cube->player.pos[Y]);
}

void	render_minimap(t_cube *cube)
{
	t_minimap	minimap;

	minimap.map = NULL;
	cube->minimap_data = minimap;
	minimap.img = &cube->minimap;
	minimap.view_dist = 4;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	calculate_minimap_offset(&minimap, cube);
	update_player_position(cube);
	minimap.map = generate_minimap(cube, &minimap);
	if (!minimap.map)
		exit_program(cube, 1, "Error: minimap generation failed");
	render_minimap_image(cube, &minimap);
	free_tab((void **)minimap.map);
}

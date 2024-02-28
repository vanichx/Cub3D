/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:26 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/28 14:54:51 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_minimap_character(t_cube *d, t_minimap *m, int x, int y)
{
	if ((int)d->player.m_pos.x == (x + m->offset_x)
		&& (int)d->player.m_pos.y == (y + m->offset_y))
		return ('N');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == '1')
		return ('1');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == '2')
		return ('2');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == '3')
		return ('3');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == '4')
		return ('4');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == 'F')
		return ('0');
	else if (d->map.map[y + m->offset_y][x + m->offset_x] == '0')
		return ('0');
	else
		return ('\0');
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
		if ((y + m->offset_y) < d->map.map_height && (size_t)
			(x + m->offset_x) < ft_strlen(d->map.map[y + m->offset_y]))
			line[x] = get_minimap_character(d, m, x, y);
		x++;
	}
	return (line);
}

char	**generate_minimap(t_cube *cube, t_minimap *minimap)
{
	char	**mmap;
	int		y;

	mmap = ft_calloc(cube->map.map_height + 1, sizeof * mmap);
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

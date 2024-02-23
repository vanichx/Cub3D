/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:26 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/23 16:46:11 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if ((y + m->offset_y) < d->map.map_height && (size_t)(x + m->offset_x) < strlen(d->map.map[y + m->offset_y]))
		{
			if ((int)d->player.m_pos.x == (x + m->offset_x) 
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
		}
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


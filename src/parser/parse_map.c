/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:43:14 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 16:53:12 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	calculate_map_size(int fd, t_cube *cube)
{
	int		i;
	char	*line;
	int		is_map_started;

	i = 0;
	is_map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			is_map_started = 1;
			if ((size_t)cube->map.map_width < ft_strlen(line))
					cube->map.map_width = ft_strlen(line);
			i++;
		}
		else if (is_map_started)
			break;
		free(line);
		line = get_next_line(fd);
	}
	cube->map.map_height = i;
	close(fd);
}

char	**handle_map(int fd, char *map_path, char **map, t_cube *cube)
{
	int i;
	char *line;

	i = 0;
	calculate_map_size(fd, cube);
	
	int m_h = cube->map.map_height;
	int m_w = cube->map.map_width;
	read_file("map.cub", &fd);
	
	printf("m_h: %d\n", m_h);
	printf("m_w: %d\n", m_w);
	*map = malloc(m_h * sizeof(char *));
	if (!*map)
		return (NULL);
	while (i < m_h)
	{
		line = get_next_line(fd);

		printf("%s\n", line);
		if (line[0] == ' ' || line[0] == '1')
		{
			map[i] = strncpy(ft_calloc(m_w + 1, sizeof(char)), line, m_w);
			i++;
		}
		free(line);
	}
	return (map);
}
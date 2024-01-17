/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:43:14 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 16:14:42 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (cube->map.map_width < ft_strlen(line))
				cube->map.map_width = ft_strlen(line);
			i++;
		}
		else if (is_map_started)
			break;
		free(line);
		line = get_next_line(fd);
	}
	cube->map.map_height = i;
}

void	handle_map(int fd, char **map, t_cube *cube)
{
	char *line;
	int i = 0;


	// Calculate the map size
	calculate_map_size(fd, cube);
	
	printf("map_width: %d\n", cube->map.map_width);
	printf("map_height: %d\n", cube->map.map_height);
	// Allocate memory for the 2D array
	*map = malloc(cube->map.map_height * sizeof(char *));
	if (*map == NULL)
	{
		// Handle error
		return;
	}

	line = get_next_line(fd);
	while (line)
	{
		// Allocate memory for each line in the 2D array
		map[i] = malloc(cube->map.map_width * sizeof(char));
		if (map[i] == NULL)
		{
			// Handle error
			return;
		}

		// Copy the line into the 2D array
		ft_strncpy(map[i], line, cube->map.map_width);

		// Replace spaces with zeros
		for (int j = 0; j < cube->map.map_width; j++)
		{
			if (map[i][j] == ' ')
			{
				map[i][j] = '0';
			}
		}

		free(line);
		line = get_next_line(fd);
		i++;
	}
}
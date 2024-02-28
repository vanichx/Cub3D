/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:43:51 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/28 17:34:02 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int find_longest_line(char **map)
{
	int i;
	int longest;

	i = 0;
	longest = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	return (longest + 1);
}

static int calculate_map_lines(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char **allocate_new_map(int map_lines, int longest_line)
{
    int i;
    char **new_map;

	i = 0;
	new_map = malloc(sizeof(char *) * (map_lines + 1));
    while (i < map_lines)
    {
        new_map[i] = malloc(sizeof(char) * (longest_line + 1));
        i++;
    }
    return (new_map);
}

void copy_map_content(char **new_map, char **map, int longest_line)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && j < longest_line)
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		while (j < longest_line)
		{
			new_map[i][j] = '0';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
}

char **square_map(char **map)
{
    int map_lines;
    int longest_line;
    char **new_map;
	
	map_lines = calculate_map_lines(map);
	longest_line = find_longest_line(map);
	new_map = allocate_new_map(map_lines, longest_line);
    copy_map_content(new_map, map, longest_line);
    return (new_map);
}

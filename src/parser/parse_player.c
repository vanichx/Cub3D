/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 15:05:57 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_player(t_cube *cube)
{
	int	i;
	int player_start_positions = 0;

	i = 0;
	while (cube->map.map[i])
	{
		if (is_player(cube->map.map[i]))
		{
			player_start_positions++;
			cube->player.matrix_pos.x = is_player(cube->map.map[i]);
			cube->player.matrix_pos.y = i;
			cube->player.init_view = cube->map.map[(int)cube->player.matrix_pos.y][(int)cube->player.matrix_pos.x];
			cube->player.move = 0;
			cube->player.rotate = 0;
			cube->player.player_speed = PLAYER_SPEED;
			cube->player.player_rot_speed = PLAYER_ROT_SPEED;
		}
		i++;
	}
	if (player_start_positions == 0)
		return (fprintf(stderr, "❌ Cube error: No player\n"), 1);
	return (0);
}

bool is_map_enclosed(char **map, int width, int height)
{
    // Check if the outermost edges have '1', indicating an open map
    for (int i = 0; i < height; i++)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return false;
    }

    for (int j = 0; j < width; j++)
    {
        if (map[0][j] != '1' || map[height - 1][j] != '1')
            return false;
    }

    // Check if the inner area is enclosed by '1'
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            if (map[i][j] != '1')
                return false;
        }
    }

    // Map is enclosed by walls
    return true;
}

void square_map(t_map *map)
{
    int i;
    int j;
    char *line;

    i = 0;
    while (i < map->map_height)
    {
        j = 0; // Reset j to 0 for each new row
        if ((int)ft_strlen(map->map[i]) < map->map_width)
        {
            line = malloc(sizeof(char) * (map->map_width + 1));
            while (map->map[i][j] != '\0')
            {
                if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
                    line[j] = map->map[i][j];
                else if (map->map[i][j] != '1') // Compare with character '1'
                    line[j] = '0'; // Replace characters other than '1' with '0'
                else
                    line[j] = '1';
                j++;
            }
            while (j < map->map_width)
                line[j++] = '0';
            line[j] = '\0'; // Null terminate the new string
            free(map->map[i]);
            map->map[i] = ft_strdup(line);
            free(line);
        }
        else
        {
            while (map->map[i][j] != '\0')
            {
                if (map->map[i][j] != '1')
                    map->map[i][j] = '0'; // Replace characters other than '1' with '0'
                j++;
            }
        }
        i++;
    }
}

int check_walls(t_cube *cube)
{
    int i;
    int j;

    i = 0;
    j = 0;
    square_map(&cube->map);

    // Check if the modified map is enclosed by walls
    if (is_map_enclosed(cube->map.map, cube->map.map_width, cube->map.map_height))
    {
        // Map is enclosed by walls, handle accordingly
        return 1;
    }
    else
    {
        // Map is not enclosed by walls, handle accordingly
        return 0;
    }
}

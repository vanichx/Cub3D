/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 13:04:03 by eseferi          ###   ########.fr       */
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

#include <stdlib.h>

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

// Function implementations
int check_corner_grids(t_map *map, int i, int j) {
    if ((i == 0 && j == 0))
		return ((map->map[i][j + 1] == '1' || map->map[i + 1][j] == '1' || map->map[i + 1][j + 1] == '1'));
	else if ((i == 0 && j == map->map_width - 1))
		return (map->map[i][j - 1] == '1' || map->map[i + 1][j] == '1' || map->map[i + 1][j - 1] == '1');
	else if ((i == map->map_height - 1 && j == 0))
		return (map->map[i][j + 1] == '1' || map->map[i - 1][j] == '1' || map->map[i - 1][j + 1] == '1');
	else 
		return (map->map[i][j - 1] == '1' || map->map[i - 1][j] == '1' || map->map[i - 1][j - 1] == '1');
}

int check_top_side_grids(t_map *map, int i, int j) {
    return ((map->map[i + 1][j - 1] == '1' || map->map[i][j - 1] == '1') 
		&& (map->map[i + 1][j] == '1' || map->map[i + 1][j + 1] == '1' 
		|| map->map[i][j + 1] == '1'));
}

int check_bottom_side_grids(t_map *map, int i, int j) {
	return ((map->map[i - 1][j - 1] == '1' || map->map[i][j - 1] == '1') 
		&& (map->map[i - 1][j] == '1' || map->map[i - 1][j + 1] == '1' 
		|| map->map[i][j + 1] == '1'));
}

int check_left_side_grids(t_map *map, int i, int j) {
	return ((map->map[i - 1][j + 1] == '1' || map->map[i - 1][j] == '1') 
		&& (map->map[i][j + 1] == '1' || map->map[i + 1][j + 1] == '1' 
		|| map->map[i + 1][j] == '1'));
}

int check_right_side_grids(t_map *map, int i, int j) {
	return ((map->map[i - 1][j - 1] == '1' || map->map[i - 1][j] == '1') 
		&& (map->map[i][j - 1] == '1' || map->map[i + 1][j - 1] == '1' 
		|| map->map[i + 1][j] == '1'));
}

int check_middle_grids(t_map *map, int i, int j) {
	return ((map->map[i - 1][j - 1] == '1' || map->map[i - 1][j] == '1' 
		|| map->map[i][j - 1] == '1' || map->map[i + 1][j - 1] == '1') 
		&& (map->map[i - 1][j + 1] == '1' || map->map[i - 1][j] == '1' 
		|| map->map[i][j + 1] == '1' || map->map[i + 1][j + 1] == '1'));
}

int check_grids(t_map *map, int i, int j)
{
	if ((i == 0 && j == 0) || (i == 0 && j == map->map_width - 1) || (i == map->map_height - 1 && j == 0) || (i == map->map_height - 1 && j == map->map_width - 1))
		return (check_corner_grids(map, i, j));
	else if (i == 0 && j > 0 && j < map->map_width - 1)
		return (check_top_side_grids(map, i, j));
	else if (i == map->map_height - 1 && j > 0 && j < map->map_width - 1)
		return (check_bottom_side_grids(map, i, j));
	else if (j == 0 && i > 0 && i < map->map_height - 1)
		return (check_left_side_grids(map, i, j));
	else if (j == map->map_width - 1 && i > 0 && i < map->map_height - 1)
		return (check_right_side_grids(map, i, j));
	else if (i > 0 && i < map->map_height - 1 && j > 0 && j < map->map_width - 1)
		return (check_middle_grids(map, i, j));
	return (0);
}

int check_walls(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	square_map(&cube->map);
	while (i < cube->map.map_height)
	{
		while (j < cube->map.map_width)
		{
			if (cube->map.map[i][j] == '1')
				if (!check_grids(&cube->map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

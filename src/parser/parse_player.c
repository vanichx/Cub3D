/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 10:21:17 by ipetruni         ###   ########.fr       */
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

void	transform_spaces(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' || map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'E' || map[i][j] == 'W')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int check_walls(char **map, int map_height, int map_width)
{
	(void)map_height;
	(void)map_width;
	transform_spaces(map);
    return 1;
}
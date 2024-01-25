/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/25 17:40:03 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_player(t_cube *cube)
{
	int	i;
	int	player_start_positions;

	i = 0;
	player_start_positions = 0;
	while (cube->map.map[i])
	{
		if (is_player(cube->map.map[i]))
		{
			player_start_positions++;
			cube->player.m_pos.x = is_player(cube->map.map[i]);
			cube->player.m_pos.y = i;
			cube->player.pos.x = cube->player.m_pos.x + 0.5; // shifting the player in the center of the grid square
			cube->player.pos.y = cube->player.m_pos.y + 0.5; // shifting the player in the center of the grid square
			cube->player.init_view = cube->map.map[(int)cube->player.m_pos.y]
			[(int)cube->player.m_pos.x];
			cube->player.front = get_dir_vec(cube->player.init_view);
			cube->player.cam = get_cam_vec(cube->player.front);
			cube->player.move = 0;
			cube->player.rotate = 0;
			cube->player.player_speed = PLAYER_SPEED;
			cube->player.player_rot_speed = PLAYER_ROT_SPEED;
		}
		i++;
	}
	if (player_start_positions == 0)
		exit_program(cube, 1, NO_PLAYER);
}

static int	f_fill(t_cube *cube, int p_y, int p_x)
{
	int	c_x;
	int	c_y;
	int	map_h;

	c_x = p_x;
	c_y = p_y;
	map_h = cube->map.map_height;
	if (c_y >= map_h || cube->map.map[c_y][c_x] == ' '
		|| cube->map.map[c_y][c_x] == '\0')
		exit_program (cube, 1, UNCLOSED_MAP);
	if (c_y < 0 || c_x < 0 || cube->map.map[c_y][c_x] == '1'
		|| cube->map.map[c_y][c_x] == 'F')
		return (0);
	cube->map.map[c_y][c_x] = 'F';
	if (f_fill(cube, c_y + 1, c_x)
		|| f_fill(cube, c_y - 1, c_x)
		|| f_fill(cube, c_y, c_x + 1)
		|| f_fill(cube, c_y, c_x - 1))
		return (1);
	return (0);
}

static void	replace_spaces(char **map, int map_h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map_h)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	check_walls(t_cube *cube)
{
	replace_spaces(cube->map.map, cube->map.map_height);
	// print_map_info(cube);
	f_fill(cube, (int)cube->player.m_pos.y,
		(int)cube->player.m_pos.x);
	// print_map_info(cube);
}

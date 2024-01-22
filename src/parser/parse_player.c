/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/22 14:41:31 by eseferi          ###   ########.fr       */
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

int  f_fill(t_cube *cube, int p_y, int p_x)
{
  int    c_x;
  int    c_y;
  int    map_h;
  int    map_w;

  c_x = p_x;
  c_y = p_y;
  map_w = cube->map.map_width;
  map_h = cube->map.map_height;
//   printf("map width %d\n", map_w);
  printf("\nff pos y %d\t", c_y);
  printf("ff pos x %d\n", c_x);
  if (c_y < 0  || c_x < 0 || c_y > map_h || cube->map.map[c_y][c_x] == '1' || cube->map.map[c_y][c_x] == 'F')
	return (printf("nothing to check here \n"), 0);
  if (cube->map.map[c_y][c_x] == ' ' || cube->map.map[c_y][c_x] == '\0') {
	fprintf(stderr, "❌ Cube error: Map is not enclosed\n");
	exit_program (cube, 1);
  }
  cube->map.map[c_y][c_x] = 'F';
  if ( f_fill(cube, c_y + 1, c_x) ||
	f_fill(cube, c_y - 1, c_x) ||
	f_fill(cube, c_y, c_x + 1) ||
	f_fill(cube, c_y, c_x - 1))
	return (1);
  return (0);
}

int check_walls(t_cube *cube)
{
	if (f_fill(cube, (int)cube->player.matrix_pos.y, (int)cube->player.matrix_pos.x))
		return (print_map_info(cube), fprintf(stderr, "❌ Cube error: Map is not enclosed\n"), 1);
	print_map_info(cube);
	return (0);
}

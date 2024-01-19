/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 08:57:10 by eseferi          ###   ########.fr       */
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

// int check_walls(char **map)
// {
// 	if (!line)
// 	while (*map)
// 	{
// 		if (!line_has_walls(*map))
// 			return (fprintf(stderr, "❌ Cube error: Map is not closed\n"), 1);
// 		map++;
// 	}
// }
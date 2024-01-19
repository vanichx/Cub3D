/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 08:48:10 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	cube->map.texture[cube->map.num_textures] = ft_strdup(trimmed_line + 3);
	cube->map.num_textures++;
}

void	parse_floor_color(char *trimmed_line, t_cube *cube, char *line)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.floor_col);
	if (parse_result == 0)
	{
		printf("Error: Not enough color values\n");
		free(trimmed_line);
		free(line);
	}
	else if (parse_result == -1)
	{
		printf("Error: Color value out of range\n");
		free(trimmed_line);
		free(line);
	}
}

void	parse_ceiling_color(char *trimmed_line, t_cube *cube, char *line)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.ceiling_col);
	if (parse_result == 0)
	{
		printf("Error: Not enough color values\n");
		free(trimmed_line);
		free(line);
	}
	else if (parse_result == -1)
	{
		printf("Error: Color value out of range\n");
		free(trimmed_line);
		free(line);
	}
}

int	parse_map_lines(char *line, char **buffer, t_cube *cube)
{
	static int	map_height = 0;
	static int	map_width = 0;

	if (is_valid_line(line) > 1)
		return (EXIT_FAILURE);
	buffer[map_height] = strdup(line);
	if (buffer[map_height] == NULL)
		return (EXIT_FAILURE);
	map_height++;
	if ((int)ft_strlen(line) > map_width)
		map_width = ft_strlen(line);
	cube->map.map_height = map_height;
	cube->map.map_width = map_width;
	return (EXIT_SUCCESS);
}

void	print_map_info(t_cube *cube)
{
	printf("\t\tThe cube info is:\n");
	printf("\n\n\tThe map structure is:\n");
	for (int j = 0; cube->map.map[j] != 0; j++)
			printf("map_line :%s", cube->map.map[j]);
	printf("\n\n\tThe map texture are is:\n");
	for (int j = 0; j < cube->map.num_textures; j++)
			printf("%s\n", cube->map.texture[j]);
	printf("\n\nThe floor colors are:\n");
	for (int j = 0; j < 3; j++)
			printf("%d ", cube->map.floor_col[j]);
	printf("\n\nThe ceiling colors are:\n");
	for (int j = 0; j < 3; j++)
			printf("%d ", cube->map.ceiling_col[j]);
	printf("\n\nPlayer's data are:\n");
	printf("player's x position: %f\n", cube->player.matrix_pos.x);
	printf("player's y position: %f\n", cube->player.matrix_pos.y);
	printf("player's initial view: %c\n", cube->player.init_view);
	printf("player's move: %d\n", cube->player.move);
	printf("player's rotate: %d\n", cube->player.rotate);
	printf("player's speed: %f\n", cube->player.player_speed);
	printf("player's rotation speed: %f\n", cube->player.player_rot_speed);
	printf("\n\nmap_height: %d\n", cube->map.map_height);
	printf("\nmap_width: %d\n", cube->map.map_width);
}

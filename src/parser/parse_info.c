/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/25 18:40:59 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	char *texture_path;
	int	h;
	int	w;

	h = 64;
	w = 64;
	if (cube->map.num_textures >= MAX_NUM_TEXT)
		exit_program(cube, 1, TOO_MANY_TEXTURES);
	texture_path = ft_strdup(trimmed_line + 3);
	if (texture_path == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	cube->map.texture[cube->map.num_textures] = texture_path;
	cube->map.text[cube->map.num_textures] = mlx_xpm_file_to_image(cube->screen.mlx, \
		cube->map.texture[cube->map.num_textures], &h, &w);
	cube->map.num_textures++;
}

void	parse_floor_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.floor_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_FLOOR);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_FLOOR);
	}
}

void	parse_ceiling_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.ceiling_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_CEIL);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_CEIL);
	}
}

void	parse_map_lines(char *line, char **buffer, t_cube *cube)
{
	static int	map_height = 0;
	static int	map_width = 0;

	if (is_valid_line(line, cube) > 1)
		exit_program(cube, 1, MULT_PLAYERS);
	buffer[map_height] = custom_strdup(line);
	if (buffer[map_height] == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	map_height++;
	if ((int)ft_strlen(line) > map_width)
		map_width = ft_strlen(line);
	cube->map.map_height = map_height;
	cube->map.map_width = map_width;
}

void	print_map_info(t_cube *cube)
{
	int	j;

	j = -1;
	printf("\t\tThe cube info is:\n");
	printf("\n\n\tThe map structure is:\n");
	while (cube->map.map[++j] != 0)
		printf("%s\n", cube->map.map[j]);
	j = -1;
	printf("\n\n\tThe map texture are is:\n");
	while (++j < cube->map.num_textures)
		printf("%s\n", cube->map.texture[j]);
	printf("\n\nThe floor colors are:\n");
	j = -1;
	while (++j < 3)
		printf("%d ", cube->map.floor_col[j]);
	j = -1;
	printf("\n\nThe ceiling colors are:\n");
	while (++j < 3)
		printf("%d ", cube->map.ceiling_col[j]);
	printf("\n\nPlayer's data are:\n");
	printf("player's x position: %f\n", cube->player.m_pos.x);
	printf("player's y position: %f\n", cube->player.m_pos.y);
	printf("\n\nmap_height: %d\n", cube->map.map_height);
	printf("\nmap_width: %d\n", cube->map.map_width);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 03:09:03 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_textures(char *trimmed_line, t_cube *cube)
{
	cube->map.texture[cube->map.num_textures] = ft_strdup(trimmed_line + 3);
	cube->map.num_textures++;
}

static void	handle_floor_color(char *trimmed_line, t_cube *cube, char *line)
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

static void	handle_ceiling_color(char *trimmed_line, t_cube *cube, char *line)
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

int	parse_textures(char **map_info, t_cube *cube)
{
	char *trimmed_line;
	char **buffer;
	int i;

	i = 0;
	buffer = malloc(sizeof(char *) * MAX_LINES);
	if (!buffer)
		return (fprintf(stderr, "❌ Malloc error: %s\n", strerror(errno)));
	while (map_info[i])
	{
		trimmed_line = trim_whitespace(map_info[i]);
		if (!ft_strncmp(trimmed_line, "NO ", 3)
			|| !ft_strncmp(trimmed_line, "SO ", 3)
			|| !ft_strncmp(trimmed_line, "EA ", 3)
			|| !ft_strncmp(trimmed_line, "WE ", 3))
			validate_textures(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "F ", 2))
			handle_floor_color(trimmed_line, cube, map_info[i]);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			handle_ceiling_color(trimmed_line, cube, map_info[i]);
		else if (trimmed_line[0] == '1' || trimmed_line[0] == ' ') {
			if (copy_map_lines(map_info[i], buffer, cube)) {
				return (free(trimmed_line), EXIT_FAILURE);
			}
		}
		free(trimmed_line);
		i++;
	}
	cube->map.map = malloc(sizeof(char *) * cube->map.map_height);
	for (int j = 0; j < cube->map.map_height; j++) {
		cube->map.map[j] = strdup(buffer[j]);
		if (cube->map.map[j] == NULL) {
			fprintf(stderr, "Failed to duplicate string.\n");
			return EXIT_FAILURE;
		}
	}
	for (int j = 0; j < cube->map.map_height; j++) {
		free(buffer[j]);
		buffer[j] = NULL;
	}
	free(buffer);
	//print_cube_info(cube);
	return (0);
}

int copy_map_lines(char *line, char **buffer, t_cube *cube)
{
	static int map_height = 0;
	static int map_width = 0;
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

void print_cube_info(t_cube *cube)
{
	for (int j = 0; cube->map.map[j] != 0; j++)
			printf("map_line :%s", cube->map.map[j]);
	for (int j = 0; j < cube->map.num_textures; j++)
			printf("%s\n", cube->map.texture[j]);
	for (int j = 0; j < 3; j++)
			printf("%d\n", cube->map.floor_col[j]);
	for (int j = 0; j < 3; j++)
			printf("%d\n", cube->map.ceiling_col[j]);
	printf("map_height: %d\n", cube->map.map_height);
	printf("map_width: %d\n", cube->map.map_width);
}

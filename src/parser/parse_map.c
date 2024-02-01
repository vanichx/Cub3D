/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:16:31 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/01 11:35:13 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	proceed_mapfile(char **map_file, char **buffer, t_cube *cube)
{
	int		i;
	char	*trimmed_line;

	i = -1;
	while (map_file[++i])
	{
		trimmed_line = trim_whitespace(map_file[i]);
		if (!ft_strncmp(trimmed_line, "NO ", 3)
			|| !ft_strncmp(trimmed_line, "SO ", 3)
			|| !ft_strncmp(trimmed_line, "EA ", 3)
			|| !ft_strncmp(trimmed_line, "WE ", 3))
			parse_textures(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "F ", 2))
			parse_floor_color(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			parse_ceiling_color(trimmed_line, cube);
		else if (trimmed_line[0] == '1' || trimmed_line[0] == ' '
			|| trimmed_line[0] == '0')
			parse_map_lines(map_file[i], buffer, cube);
		free(trimmed_line);
	}
}

void check_file_loc(t_cube *cube, char *text)
{
	if (ft_strncmp(text, "./textures/", 11))
		exit_program(cube, 1, TEXT_LOC_ERR);
	if (ft_strcmp(&text[ft_strlen(text) - 4], ".xpm"))
		exit_program(cube, 1, TEXT_EXT_ERR);
}

void validate_text(t_cube *cube, char *text)
{
	if (ft_strlen(text) < 16)
		exit_program(cube, 1, TEXT_ERR_FORMAT);
	// if (check_text_dir(text) == -1)
	// 	exit_program(cube, 1, TEXT_DIR_ERR);
	check_file_loc(cube, text);
}

void parse_textures_files(t_cube *cube)
{
	int i;
	i = NO;
	while (i <= WE)
	{
		printf("texture[%d]: %s\n", i, cube->map.texture[i]);
		validate_text(cube, cube->map.texture[i]);
		i++;
	}
}

void	parse_map(char **map_file, t_cube *cube)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!buffer)
		exit_program(cube, 1, MALLOC_ERROR);
	proceed_mapfile(map_file, buffer, cube);
	cube->map.map = malloc(sizeof(char *) * (cube->map.map_height + 1));
	if (!cube->map.map)
		exit_program(cube, 1, MALLOC_ERROR);
	while (i < cube->map.map_height)
	{
		cube->map.map[i] = ft_strdup(buffer[i]);
		if (cube->map.map[i++] == NULL)
			exit_program(cube, 1, DUPLICATE_ERROR);
	}
	cube->map.map[cube->map.map_height] = NULL;
	free_2darray(buffer);
	parse_player(cube);
	parse_textures_files(cube);
}

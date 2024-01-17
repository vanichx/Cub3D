/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 14:42:49 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_texture(char *trimmed_line, t_cube *cube)
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

void	handle_textures_info(int fd, t_cube *cube)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = trim_whitespace(line);
		if (!ft_strncmp(trimmed_line, "NO ", 3)
			|| !ft_strncmp(trimmed_line, "SO ", 3)
			|| !ft_strncmp(trimmed_line, "EA ", 3)
			|| !ft_strncmp(trimmed_line, "WE ", 3))
			handle_texture(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "F ", 2))
			handle_floor_color(trimmed_line, cube, line);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			handle_ceiling_color(trimmed_line, cube, line);
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
}

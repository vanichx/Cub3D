/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:16:31 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 08:31:03 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	proceed_mapfile(char **map_file, char **buffer, t_cube *cube)
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
			parse_floor_color(trimmed_line, cube, map_file[i]);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			parse_ceiling_color(trimmed_line, cube, map_file[i]);
		else if (trimmed_line[0] == '1' || trimmed_line[0] == ' ')
			if (parse_map_lines(map_file[i], buffer, cube))
				return (free(trimmed_line), EXIT_FAILURE);
		free(trimmed_line);
	}
	return (EXIT_SUCCESS);
}

int	parse_map(char **map_file, t_cube *cube)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!buffer)
		return (fprintf(stderr, "❌ Malloc error: %s\n", strerror(errno)));
	if (proceed_mapfile(map_file, buffer, cube))
		return (EXIT_FAILURE);
	cube->map.map = malloc(sizeof(char *) * (cube->map.map_height + 1));
	while (i < cube->map.map_height)
	{
		cube->map.map[i] = ft_strdup(buffer[i]);
		if (cube->map.map[i++] == NULL)
		{
			fprintf(stderr, "❌ Duplicae error: Failed to duplicate string.\n");
			return (free_2darray(buffer), EXIT_FAILURE);
		}
	}
	cube->map.map[cube->map.map_height] = NULL;
	free_2darray(buffer);
	return (EXIT_SUCCESS);
}

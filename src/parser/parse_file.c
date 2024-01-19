/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 07:02:37 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_file_and_store_lines(char *map_path, char ***buffer)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	*buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!read_file(map_path, &fd))
		return (fprintf(stderr, "❌ Read error: Failed to read the file\n"));
	line = get_next_line(fd);
	while (line)
	{
		(*buffer)[count] = ft_strdup(line);
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	copy_lines_to_map_file(char ***map_file, char **buffer, int count)
{
	int		i;

	i = 0;
	*map_file = malloc((count + 1) * sizeof(char *));
	if (!*map_file)
		return (fprintf(stderr, \
			"❌ Malloc error: Failed to Allocate the map buffer\n"));
	while (i < count)
	{
		(*map_file)[i] = ft_strdup(buffer[i]);
		if ((*map_file)[i++] == NULL)
			return (free_2darray(buffer), fprintf(stderr, \
				"❌ Malloc error: Failed to Allocate the map buffer\n"));
	}
	(*map_file)[count] = NULL;
	free_2darray(buffer);
	return (EXIT_SUCCESS);
}

int	parse_file(char *map_path, char ***map_file)
{
	char	**buffer;
	int		count;

	count = read_file_and_store_lines(map_path, &buffer);
	if (!count)
		return (EXIT_FAILURE);
	return (copy_lines_to_map_file(map_file, buffer, count));
}

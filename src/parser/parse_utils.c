/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 07:07:29 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	else
		return (false);
}

int	is_valid_line(char *line)
{
	static int	player_dir = 0;
	int			i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			return (fprintf(stderr, \
				"❌ Cube error: Invalid character in map\n"));
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			player_dir++;
		i++;
	}
	if (player_dir > 1)
		return (fprintf(stderr, "❌ Cube error: Multiple players\n"), -1);
	return (player_dir);
}

int	read_file(char *map_path, int *fd)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error\nCould not open file %s\n", map_path);
		return (0);
	}
	return (1);
}

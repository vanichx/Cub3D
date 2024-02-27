/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/27 18:25:00 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void 	multiple_error(int player_dir, int info[3])
{
	if (player_dir > 1)
		exit_program(NULL, 1, MULT_PLAYERS);
	if (info[DOOR] > 1)
		exit_program(NULL, 1, MULT_DOORS);
	if (info[KEY] > 1)
		exit_program(NULL, 1, MULT_KEYS);
	if (info[ENEMY] > 1)
		exit_program(NULL, 1, MULT_ENEMIES);
}

bool	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == '2' || c == '3' || c == '4'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	else
		return (false);
}

int	is_valid_line(char *line, t_cube *cube)
{
	static int	player_dir = 0;
	static int  info[3] = {0, 0, 0};
	int			i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			exit_program(cube, 1, INV_CHARS);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			player_dir++;
		if (line[i] == '2')
			info[DOOR]++;
		if (line[i] == '3')
			info[KEY]++;
		if (line[i] == '4')
			info[ENEMY]++;
		i++;
	}
	if (player_dir > 1 || info[DOOR] > 1 || info[KEY] > 1 || info[ENEMY] > 1)
		multiple_error(player_dir, info);
	return (player_dir);
}

void	read_file(char *map_path, int *fd, t_cube *cube)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd < 0)
		exit_program(cube, 1, READ_FILE_ERROR);
}

bool	line_has_walls(char *line)
{
	while (*line)
	{
		if (*line == '1')
			return (true);
		line++;
	}
	return (false);
}

int 	is_key(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '3')
			return (pos);
		pos++;
	}
	return (0);
}

int 	is_door(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '2')
			return (pos);
		pos++;
	}
	return (0);
}

int 	is_enemy(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '4')
			return (pos);
		pos++;
	}
	return (0);
}

int	is_player(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == 'N' || line[pos] == 'S'
			|| line[pos] == 'E' || line[pos] == 'W')
			return (pos);
		pos++;
	}
	return (0);
}

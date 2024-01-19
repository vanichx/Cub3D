/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 02:47:41 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*trim_whitespace(const char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(strlen(str) + 1);
	while (ft_isspace((unsigned char)str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			while (ft_isspace((unsigned char)str[i]))
				i++;
			if (str[i] != '\0')
				result[j++] = ' ';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

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
			return (fprintf(stderr, "❌ Cube error: Invalid character in map\n"));
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			player_dir++;
		i++;
	}
	if (player_dir > 1)
		return (fprintf(stderr, "❌ Cube error: Multiple players\n"), -1);
	return (player_dir);
}
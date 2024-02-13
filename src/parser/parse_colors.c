/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:24:47 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 13:58:59 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_color_values(char *line, int *color)
{
	int		i;
	int		j;
	char	*num_start;
	int		commas;

	i = 2;
	j = 0;
	commas = 0;
	num_start = &line[i];
	while (line[i] != '\0' && j < COLORS_COMPONENTS)
	{
		if (line[i] == ',')
		{
			commas++;
			if (commas > 2)
				return (-1);
			line[i] = '\0';
			color[j] = ft_atoi(num_start);
			num_start = &line[i + 1];
			j++;
		}
		else if (line[i + 1] == '\0')
		{
			color[j] = ft_atoi(num_start);
			j++;
		}
		i++;
	}
	return (j);
}

static int	check_color_values(int *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			return (-1);
		i++;
	}
	return (1);
}

int	parse_color_code(char *line, int *color)
{
	int	check;

	check = parse_color_values(line, color);
	if (check != COLORS_COMPONENTS)
		return (0);
	check = check_color_values(color);
	if (check == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:15:43 by eseferi           #+#    #+#             */
/*   Updated: 2024/01/19 07:07:55 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	if (parse_file(map_path, &cube->map.map_file))
		return (EXIT_FAILURE);
	if (parse_map(cube->map.map_file, cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

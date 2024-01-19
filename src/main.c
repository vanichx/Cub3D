/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 07:10:37 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../mlx/mlx.h"

bool	check_args(int argc, char *argv[])
{
	if (argc != 2)
		return (fprintf(stderr, "❌ Cube error: Wrong number of arguments\n"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (fprintf(stderr, "❌ Cube error: Wrong file extension\n"));
	if (ft_strncmp(argv[1], "maps/", 5))
		return (fprintf(stderr, "❌ Cube error: Wrong file location\n"));
	if (ft_strlen(argv[1]) < 10)
		return (fprintf(stderr, "❌ Cube error: Wrong file naming\n"));
	return (EXIT_SUCCESS);
}

bool	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	if (parse_file(map_path, &cube->map.map_file))
		return (EXIT_FAILURE);
	if (parse_map(cube->map.map_file, cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	t_cube cube;
	
	ft_bzero(&cube, sizeof(t_cube));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (parse(argv[1], &cube))
		return (cleanup(&cube), EXIT_FAILURE);
	// if (init_window(&cube.screen))
	// 	return (EXIT_FAILURE);
	cleanup(&cube);
	
	// mlx_loop(&cube.screen.mlx);
}

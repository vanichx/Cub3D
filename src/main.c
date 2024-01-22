/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/22 15:14:52 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "../mlx/mlx.h"

bool	check_args(int argc, char *argv[])
{
	if (argc != 2)
		return (fprintf(stderr, WRONG_NUM_OF_ARGS));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (fprintf(stderr, WRONG_FILE_EXT));
	if (ft_strncmp(argv[1], "maps/", 5))
		return (fprintf(stderr, WRONG_FILE_LOC));
	if (ft_strlen(argv[1]) < 10)
		return (fprintf(stderr, WRONG_FILE_NAMING));
	return (EXIT_SUCCESS);
}

bool	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	if (parse_file(map_path, &cube->map.map_file) 
		|| parse_map(cube->map.map_file, cube)
		|| parse_player(cube))
		return (EXIT_FAILURE);
	print_map_info(cube);
	if (check_walls (cube))
		return (printf("not closed map \n"), EXIT_FAILURE);
	printf("Map is close\n");
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

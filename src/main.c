/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/23 11:54:59 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_close(t_cube *cube)
{
	cleanup(cube);
	return (0);
}

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

void	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	parse_file(map_path, &cube->map.map_file, cube);
	parse_map(cube->map.map_file, cube);
	parse_player(cube);
	print_map_info(cube);
	check_walls (cube);
}

int main(int argc, char *argv[])
{
	t_cube cube;
	
	ft_bzero(&cube, sizeof(t_cube));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	parse(argv[1], &cube);
	if (init_window(&cube.screen))
		return (EXIT_FAILURE);
	if (hooking(&cube))
		return (EXIT_FAILURE);
	cleanup(&cube);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/09 09:01:25 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_close(t_cube *cube)
{
	cleanup(cube, EXIT_SUCCESS);
	return (0);
}

void	allocate_text_pixels(t_cube *cube)
{
	int i;
	
	i = 0;
	cube->wall_text.text_pixels = ft_calloc(cube->screen.height + 1, sizeof * cube->wall_text.text_pixels);
	if (cube->wall_text.text_pixels == NULL)
		exit_program(cube, 1, MALLOC_ERROR);
	while (i < cube->screen.height)
	{
		cube->wall_text.text_pixels[i] = ft_calloc(cube->screen.width + 1, sizeof * cube->wall_text.text_pixels);
		if (cube->wall_text.text_pixels[i] == NULL)
			exit_program(cube, 1, MALLOC_ERROR);
		i++;
	
	}
}

void	check_args(int argc, char *argv[])
{
	if (argc != 2)
		exit_program(NULL, EXIT_FAILURE, WRONG_NUM_OF_ARGS);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_EXT);
	if (ft_strncmp(argv[1], "maps/", 5))
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_LOC);
	if (ft_strlen(argv[1]) < 10)
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_NAMING);
}

void	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	parse_file(map_path, &cube->map.map_file, cube);
	parse_map(cube->map.map_file, cube);
	print_map_info(cube);
	check_walls (cube);
	allocate_text_pixels(cube);
}

int main(int argc, char *argv[])
{
	t_cube cube;
	
	check_args(argc, argv);
	ft_bzero(&cube, sizeof(t_cube));
	init_window(&cube);
	parse(argv[1], &cube);
	// game_loop(&cube);
	if (hooking(&cube))
		return (EXIT_FAILURE);
}

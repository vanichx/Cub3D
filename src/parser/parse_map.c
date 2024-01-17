/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 14:44:26 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all(t_cube *cube)
{
	cube->fov = 60;
	cube->map.map_x = 0;
	cube->map.map_y = 0;
	cube->map.num_line = 0;
	cube->map.num_textures = 0;
	cube->map.data_type = 0;
	cube->map.map_parsing = false;
	cube->player.pos.x = 0;
	cube->player.pos.y = 0;
	cube->player.player_speed = 10;
	cube->player.player_rot_speed = 4;
	cube->player.move = 0;
	cube->player.rotate = 0;
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

int	handle_map_file(int fd, char **map, t_cube *cube)
{
	handle_textures_info(fd, cube);
	//convert the map to a 2d array
	return (1);
}

bool	parse_and_init(char *map_path, t_cube *cube)
{
	int		fd;
	char	**map;

	//Initialize all the variables
	init_all(cube);
	//Read the map file
	if (!read_file(map_path, &fd))
		return (false);
	//Allocate memory for the map
	map = ft_calloc(sizeof(char **), 1);
	if (!map)
		return (false);
	cube->map.map = map;
	//Parse the map file
	if (!handle_map_file(fd, map, cube))
		return (false);
	//Print the map	
	close(fd);
	return (EXIT_SUCCESS);
}

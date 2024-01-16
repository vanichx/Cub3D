/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:49 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all(t_cube *cube)
{
	cube->fov = 60;
	cube->map.map_x = 0;
	cube->map.map_y = 0;
	cube->map.num_line = 0;
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

int find_player_position(char *line, t_cube *cube)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			cube->player.pos.x = i;
			cube->player.pos.y = cube->map.map_y;
			cube->player.init_view = line[i];
			return (1);
		}
		i++;
	}
	return (0);
}


int handle_map_file(int fd, char **map, t_cube *cube)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		{
			cube->map.texture[cube->map.num_textures] = ft_strdup(line + 3);
			cube->map.num_textures++;
		}
		else if (!ft_strncmp(line, "F ", 2) || ft_strncmp(line, "C ", 2))
		{
			cube->map.floor_col[0] = ft_atoi(line + 2);
			cube->map.floor_col[1] = ft_atoi(line + 2);
			cube->map.floor_col[2] = ft_atoi(line + 2);
		}
		free(line);
		printf("im here\n");
		line = get_next_line(fd);
	}
	printf("num_textures: %d\n", cube->map.num_textures);
	for (int i = 0; i < cube->map.num_textures; i++)
		printf("texture[%d]: %s\n", i, cube->map.texture[i]);
	return (1);
}



bool	find_valid_character(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

bool is_player_direction(char ch)
{
	return (ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E');
}






/// MAIN PARSING FUNCTION
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

	//Parse the map file
	if (!handle_map_file(fd, map, cube))
		return (false);	

	//Print the map

	return (EXIT_SUCCESS);
}

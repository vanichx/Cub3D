/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/17 11:46:32 by ipetruni         ###   ########.fr       */
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


int handle_map_file(int fd, char **map, t_cube *cube)
{
	handle_textures_info(fd, cube);
	

	
	
	
	return (1);
}



void handle_textures_info(int fd, t_cube *cube)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = trim_whitespace(line);
		if (!ft_strncmp(trimmed_line, "NO ", 3) || !ft_strncmp(trimmed_line, "SO ", 3) || !ft_strncmp(trimmed_line, "EA ", 3) || !ft_strncmp(trimmed_line, "WE ", 3))
		{
			cube->map.texture[cube->map.num_textures] = ft_strdup(trimmed_line + 3);
			cube->map.num_textures++;
		}
		else if (!ft_strncmp(trimmed_line, "F ", 2))
			parse_color_code(trimmed_line, cube->map.floor_col);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			parse_color_code(trimmed_line, cube->map.ceiling_col);
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
	printf("num_textures: %d\n", cube->map.num_textures);
	printf("textures: %s, %s, %s, %s\n", cube->map.texture[0], cube->map.texture[1], cube->map.texture[2], cube->map.texture[3]);
	printf("floor: %d, %d, %d\n", cube->map.floor_col[0], cube->map.floor_col[1], cube->map.floor_col[2]);
	printf("ceiling: %d, %d, %d\n", cube->map.ceiling_col[0], cube->map.ceiling_col[1], cube->map.ceiling_col[2]);
}

void parse_color_code(char *line, int *color)
{
	int i;
	int j; 
	int num;

	i = 0;
	j = 0;
	num = 0;
	line += 2;
	while (j < 3)
	{
		if (line[i] == ',' || line[i+1] == '\0')
		{
			color[j] = num;
			num = 0;
			j++;
		}
		else
		{
			num = num * 10 + (line[i] - '0');
		}
		i++;
	}
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

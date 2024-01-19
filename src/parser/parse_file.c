/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/19 04:57:06 by eseferi          ###   ########.fr       */
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

int	validate_map(char **map, t_cube *cube)
{
	if (parse_textures(map, cube))
		return (EXIT_FAILURE);
	// // for(int i = 0; i < cube->map.map_height; i++)
	// // 	printf("%s\n", map[i]);
	// close(fd);
	return (EXIT_SUCCESS);
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


int	count_lines_copy(char *map_path, char ***map_info)
{
	int		fd;
	char	*line;
	int		count;
	char	**buffer;
	int		i;

	i = 0;
	count = 0;
	buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!read_file(map_path, &fd))
		return (fprintf(stderr, "❌ Read error: Failed to read the file\n"));
	line = get_next_line(fd);
	while (line)
	{
		buffer[count] = ft_strdup(line);
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	*map_info = malloc((count + 1) * sizeof(char *));
	if (!*map_info)
		return (fprintf(stderr, "❌ Malloc error: Failed to Allocate the map buffer\n"));
	while (i < count)
	{
		(*map_info)[i] = ft_strdup(buffer[i]);
		if ((*map_info)[i++] == NULL)
			return (free_2darray(buffer) ,fprintf(stderr, "❌ Malloc error: Failed to Allocate the map buffer\n"));
	}
	(*map_info)[count] = NULL;
	free_2darray(buffer);
	return (EXIT_SUCCESS);
}

bool	parse_and_init(char *map_path, t_cube *cube)
{	
	init_all(cube);		//Initialize all the variables
	if (count_lines_copy(map_path, &cube->map.map_info))	 // Count the number of lines in the file
		return (EXIT_FAILURE);
	if (validate_map(cube->map.map_info, cube))		//Parse the map file
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


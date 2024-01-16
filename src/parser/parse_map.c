#include "cub3d.h"

bool	parse_map(char *argv, t_map *map)
{
	int		fd;
	char	*line;
	char	*buffer;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
	buffer = ft_read(.r);
	while (ft_strchr(buffer, '\n') != 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
		else if (ft_strncmp(line, "NO ", 3) == 0)
			parse_texture(line, map, NORTH);
		// else if (ft_strncmp(line, "SO ", 3) == 0)
		// 	parse_texture(line, map, SOUTH);
		// else if (ft_strncmp(line, "WE ", 3) == 0)
		// 	parse_texture(line, map, WEST);
		// else if (ft_strncmp(line, "EA ", 3) == 0)
		// 	parse_texture(line, map, EAST);
		// // else if (ft_strncmp(line, "S ", 2) == 0)
		// // 	parse_texture(line, map, SPRITE);
		// else if (ft_strncmp(line, "F ", 2) == 0)
		// 	parse_color(line, map, FLOOR);
		// else if (ft_strncmp(line, "C ", 2) == 0)
		// 	parse_color(line, map, CEILING);
		// else if (ft_strncmp(line, "1 ", 2) == 0)
		// 	parse_map(line, map);
		// else if (ft_strncmp(line, "\n", 1) == 0)
		// 	;
		// else
		// 	return (fprintf(stderr, "❌ Cube error: %s\n", strerror(errno)));
		free(line);
		buffer = ft_remove_line(buffer);
	}
	free(buffer);
	close(fd);
	return (EXIT_SUCCESS);
}

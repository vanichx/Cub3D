/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/15 17:47:28 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include "../gnl/get_next_line.h"

int	print_error(t_game *game, char *err_msg)
{
	write(2, "Error\n", 7);
	write(2, err_msg, strlen(err_msg));
	if (game)
		free_game(game);
	// if (point)
	// 	free_point(point);
	exit(0);
	return (0);
}

size_t	calculate_cub_map_lines(int fd)
{
	size_t	i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}


char	**read_map(t_game *game, char *map_file)
{
	int		i;
	int		fd;
	char	*line;
	char	**map;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		print_error(game, READ_ERROR);
	map = ft_calloc(sizeof(char *), calculate_cub_map_lines(fd) + 1);
	if (!map)
		return (0);
	close(fd);
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = 0;
	close(fd);
	return (map);
}


int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W) {
		// move_player(game, game->p_y - 1, game->p_x);
		printf("W");
	}
	else if (keycode == KEY_S) {
		// move_player(game, game->p_y + 1, game->p_x);
		printf("S");
	}
	else if (keycode == KEY_A) {
		// move_player(game, game->p_y, game->p_x - 1);
		printf("A");
	}
	else if (keycode == KEY_D) {
		// move_player(game, game->p_y, game->p_x + 1);
		printf("D");
	}
	else if (keycode == KEY_ESC) {
		exit_game(game);
		
	}
	render_all(game, game->map);
	return (0);
}

static void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx,
			1280, 720,
			"cub3D");
	create_img(game);
	render_all(game, game->map);
}

int	main(void)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	game->img = ft_calloc(sizeof(t_img), 1);
	game->point = NULL;
	
	game->map = read_map(game, "maps/new.cub");
	game_init(game);
	mlx_hook(game->window, 17, 1L << 17, window_close, game);
	mlx_hook(game->window, 2, 1L << 0, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
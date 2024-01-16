/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:57:43 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 11:30:21 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include "../gnl/get_next_line.h"

void	print_w(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->wall, x, y);
}

void	print_b(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->bg, x, y);
}

void	print_c(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->coin, x, y);
}

void	print_p(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->player, x, y);
}

void	print_eo(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->exit_o, x, y);
}

void	print_ec(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->exit_c, x, y);
}

void	print_s(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->s, x, y);
}

void	print_n(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img->poe, x, y);
}

static void	print_exit(t_game *game, int j, int i)
{
	if (game->coins == 0)
		print_eo(game, j * 64, i * 64);
	else
		print_ec(game, j * 64, i * 64);
}

static void	print_all(t_game *game, char **map, int j, int i)
{
	if (map[i][j] == '1')
		print_w(game, j * 64, i * 64);
	else if (map[i][j] == '0')
		print_b(game, j * 64, i * 64);
	else if (map[i][j] == 'C')
		print_c(game, j * 64, i * 64);
	else if (map[i][j] == 'E')
		print_exit(game, j, i);
	else if (map[i][j] == 'P')
		print_p(game, j * 64, i * 64);
	else if (map[i][j] == 'S')
		print_s(game, j * 64, i * 64);
	else if (map[i][j] == 'N')
		print_n(game, j * 64, i * 64);
}


void	render_all(t_game *game, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map_h)
	{
		j = 0;
		while (j < game->map_w)
		{
			print_all(game, map, j, i);
			j++;
		}
		i++;
	}
}


void	create_img(t_game *game)
{
	game->img->bg = mlx_xpm_file_to_image(game->mlx, \
		"./img/0.xpm", &game->img->img_w, &game->img->img_h);
	game->img->wall = mlx_xpm_file_to_image(game->mlx, \
		"./img/1.xpm", &game->img->img_w, &game->img->img_h);
	game->img->coin = mlx_xpm_file_to_image(game->mlx, \
		"./img/C.xpm", &game->img->img_w, &game->img->img_h);
	game->img->exit_c = mlx_xpm_file_to_image(game->mlx, \
		"./img/EC.xpm", &game->img->img_w, &game->img->img_h);
	game->img->exit_o = mlx_xpm_file_to_image(game->mlx, \
		"./img/EO.xpm", &game->img->img_w, &game->img->img_h);
	game->img->player = mlx_xpm_file_to_image(game->mlx, \
		"./img/P.xpm", &game->img->img_w, &game->img->img_h);
	game->img->s = mlx_xpm_file_to_image(game->mlx, \
		"./img/S.xpm", &game->img->img_w, &game->img->img_h);
	game->img->poe = mlx_xpm_file_to_image(game->mlx, \
	"./img/POE.xpm", &game->img->img_w, &game->img->img_h);
	game->img->bg_count = mlx_xpm_file_to_image(game->mlx, \
		"./img/30PX.xpm", &game->img->img_w, &game->img->img_h);
}


void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->img)
		free(game->img);
	if (game)
	{
		if (game->map)
			free_map(game);
		free(game);
	}
	exit(0);
}

int	exit_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img->bg);
	mlx_destroy_image(game->mlx, game->img->wall);
	mlx_destroy_image(game->mlx, game->img->coin);
	mlx_destroy_image(game->mlx, game->img->player);
	mlx_destroy_image(game->mlx, game->img->exit_c);
	mlx_destroy_image(game->mlx, game->img->exit_o);
	mlx_destroy_image(game->mlx, game->img->bg_count);
	mlx_destroy_image(game->mlx, game->img->poe);
	mlx_destroy_image(game->mlx, game->img->s);
	mlx_destroy_window(game->mlx, game->window);
	// if (game)
	// 	free_game(game);
	// if (game->point)
	// 	free_point(game->point);
	exit(0);
}

int	window_close(t_game *game)
{
	exit_game(game);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;
	int	map_h;

	map_h = game->map_h;
	i = 0;
	while (i < map_h)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++; 
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (0 - s2[i]);
	if (s1[i] != '\0' && s2[i] == '\0')
		return (s1[i]);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n > 0)
	{
		*str++ = 0;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = nmemb * size;
	if (size && (bytes / size) != nmemb)
		return (NULL);
	ptr = malloc(bytes);
	if (NULL == ptr)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}

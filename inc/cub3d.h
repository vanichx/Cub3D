/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/15 17:45:05 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "keycodes.h"


# define READ_ERROR "Given file path is invalid!\n"


typedef struct s_img
{
	int		img_h;
	int		img_w;
	void	*wall;
	void	*bg;
	void	*coin;
	void	*player;
	void	*exit_o;
	void	*exit_c;
	void	*s;
	void	*poe;
	void	*bg_count;
}				t_img;

typedef struct s_point
{
	int		x;
	int		y;
	int		p_x;
	int		p_y;
	int		map_h;
	int		map_w;
	char	**mapcheck;
}				t_point;

typedef struct s_game
{
	char	**map;
	int		p_x;
	int		p_y;
	int		map_w;
	int		map_h;
	int		steps;
	int		coins;
	void	*window;
	void	*mlx;
	t_img	*img;
	t_point	*point;
}				t_game;

/* utils.c */
int		window_close(t_game *game);
void	free_map(t_game *game);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		exit_game(t_game *game);
void	free_game(t_game *game);
void	create_img(t_game *game);
void	render_all(t_game *game, char **map);



void	print_w(t_game *game, int x, int y);
void	print_b(t_game *game, int x, int y);
void	print_c(t_game *game, int x, int y);
void	print_p(t_game *game, int x, int y);
void	print_eo(t_game *game, int x, int y);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:29 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "keycodes.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define WIDTH 1920
#define HEIGHT 1080

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

typedef	struct s_mlx
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_mlx;

typedef struct s_map
{
	char	*texture[4];
	int		floor_col[3];
	int		ceiling_col[3];
	char	**map;
	int 	map_width;
	int		map_height;
	
}		t_map;

typedef struct s_cube
{
	t_mlx	screen;
	t_map	map;
}		t_cube;

// bool	parse_map(int argc, char **argv, t_map *map);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:50:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/25 14:38:53 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "../mlx/mlx.h"

void	ft_strdel(char **s)
{
	if (!s)
		return ;
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	*s = NULL;
}

void	free_textures(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < cube->map.num_textures)
	{
		free(cube->map.texture[i]);
		// free_image(&textures[i].img);
		i++;
	}
}

void	free_2darray(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		ft_strdel(&array[i]);
	if (array)
		free(array);
	array = NULL;
}

int	cleanup(t_cube *cube, int exit_code)
{
	free_textures(cube);
	free_2darray(cube->map.map);
	if (cube->map.map_file)
		free_2darray(cube->map.map_file);
	if (cube->screen.img)
		mlx_destroy_image(cube->screen.mlx, cube->screen.img);
	if (cube->screen.win)
		mlx_destroy_window(cube->screen.mlx, cube->screen.win);
	exit(exit_code);
	return(0);
}

void	exit_program(t_cube *cube, int exit_code, char *message)
{
	if (cube)
		cleanup(cube, exit_code);
	fprintf(stderr, "%s", message);
	exit(exit_code);
}

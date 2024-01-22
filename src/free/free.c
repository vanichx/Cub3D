/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:50:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/22 16:02:06 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

void	ft_strdel(char **s)
{
	if (!s)
		return ;
	free(*s);
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

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		ft_strdel(&array[i]);
	free(array);
	array = NULL;
}

void	cleanup(t_cube *cube)
{
	free_textures(cube);
	free_2darray(cube->map.map);
	free_2darray(cube->map.map_file);
}

void	exit_program(t_cube *cube, int exit_code, char *message)
{
	cleanup(cube);
	if (message[0] == '\0')
		exit(exit_code);
	fprintf(stderr, "%s", message);
	exit(exit_code);
}

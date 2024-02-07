/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:50:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/07 15:35:52 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

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

void	destroy_screen(t_mlx *screen)
{
	if (screen->img.img)
		mlx_destroy_image(screen->mlx, screen->img.img);
	if (screen->win)
		mlx_destroy_window(screen->mlx, screen->win);
	if (screen->mlx)
		mlx_destroy_display(screen->mlx);
}

void	destroy_wall_textures(t_textures *wall_textures, t_mlx *screen)
{
	int i;
	
	if (!wall_textures)
		return ;
	i = NO;
	while (i <= EA)
	{
		if (wall_textures->img_text[i].img)
			mlx_destroy_image(screen->mlx, wall_textures->img_text[i].img);
		i++;
	}
}

int	cleanup(t_cube *cube, int exit_code)
{
	free_textures(cube);
	free_2darray(cube->map.map);
	if (cube->map.map_file)
		free_2darray(cube->map.map_file);
	destroy_wall_textures(&cube->wall_text, &cube->screen);
	if (cube->screen.mlx)
		destroy_screen(&cube->screen);
	if (!cube)
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

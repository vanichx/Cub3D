/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 12:33:14 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_text_dir(char *text, int i)
{
	if ((i == NO && !ft_strncmp(text, "NO ", 3))
		|| (i == SO && !ft_strncmp(text, "SO ", 3))
		|| (i == EA && !ft_strncmp(text, "EA ", 3))
		|| (i == WE && !ft_strncmp(text, "WE ", 3))
		|| (i == C && !ft_strncmp(text, "C ", 2))
		|| (i == F && !ft_strncmp(text, "F ", 2)))
		return (0);
	else
		return (-1);
}

void	load_texture(t_img *img, void *mlx, char *path, t_cube *cube, int **tx)
{
	int	i[2];
	int	*buffer;

	img->img = mlx_xpm_file_to_image(mlx, path, \
	&cube->wall_text.tex_size, &cube->wall_text.tex_size);
	if (img->img == NULL)
		exit_program(cube, 1, TEXT_LOAD_ERR);
	img->casted_addr = (int *)mlx_get_data_addr(img->img, \
	&img->bpp, &img->line_length, &img->endian);
	i[Y] = -1;
	buffer = ft_calloc(1, sizeof * buffer \
	* cube->wall_text.tex_size * cube->wall_text.tex_size);
	if (!buffer)
		exit_program(cube, EXIT_FAILURE, MALLOC_ERROR);
	(*tx) = buffer;
	while (++i[Y] < cube->wall_text.tex_size)
	{
		i[X] = -1;
		while (++i[X] < cube->wall_text.tex_size)
			(*tx)[i[Y] * cube->wall_text.tex_size \
		+ i[X]] = img->casted_addr[i[Y] * cube->wall_text.tex_size + i[X]];
	}
	mlx_destroy_image(mlx, img->img);
}

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	char		*texture_path;
	static int	i = 0;

	if (cube->map.num_textures >= MAX_NUM_TEXT)
		exit_program(cube, 1, TOO_MANY_TEXTURES);
	if (check_text_dir(trimmed_line, i) == -1)
		exit_program(cube, 1, TEXT_DIR_ERR);
	if (i == F || i == C)
		texture_path = ft_strdup(trimmed_line + 2);
	else
		texture_path = ft_strdup(trimmed_line + 3);
	if (texture_path == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	cube->map.texture[cube->map.num_textures] = texture_path;
	load_texture(&cube->wall_text.img_text[cube->map.num_textures], \
		cube->screen.mlx, texture_path, cube, \
		&cube->wall_text.textures[cube->map.num_textures]);
	cube->map.num_textures++;
	i++;
}

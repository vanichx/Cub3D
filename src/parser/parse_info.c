/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/09 08:56:22 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_text_dir(char *text, int i)
{
	if ((i == NO && !ft_strncmp(text, "NO ", 3))
		|| (i == SO && !ft_strncmp(text, "SO ", 3))
		|| (i == EA && !ft_strncmp(text, "EA ", 3))
		|| (i == WE && !ft_strncmp(text, "WE ", 3)))
		return (0);
	else
		return (-1);
}

void load_texture(t_img *img, void *mlx, char *path, t_cube *cube, int **textures)
{
	int size;
	int i[2];
	
	size = TEXT_SIZE;
	img->img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	if (img->img == NULL)
		exit_program(cube, 1, TEXT_LOAD_ERR);
	img->casted_addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	i[Y] = -1;
	(*textures) = ft_calloc(1, sizeof(int) * size * size);
	if ((*textures) == NULL)
		exit_program(cube, 1, MALLOC_ERROR);
	while (++i[Y] < size)
	{
		i[X] = -1;
		while(++i[X] < size)

			(*textures)[i[Y] * size + i[X]] = img->casted_addr[i[Y] * size + i[X]];
	}
}

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	char *texture_path;
	static int i = 0;

	if (cube->map.num_textures >= MAX_NUM_TEXT)
		exit_program(cube, 1, TOO_MANY_TEXTURES);
	if (check_text_dir(trimmed_line, i) == -1)
		exit_program(cube, 1, TEXT_DIR_ERR);
	texture_path = ft_strdup(trimmed_line + 3);
	if (texture_path == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	cube->map.texture[cube->map.num_textures] = texture_path;
	load_texture(&cube->wall_text.img_text[cube->map.num_textures], cube->screen.mlx, texture_path, cube, &cube->wall_text.textures[cube->map.num_textures]);
	cube->map.num_textures++;
	i++;
}

void	parse_floor_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.floor_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_FLOOR);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_FLOOR);
	}
}

void	parse_ceiling_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.ceiling_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_CEIL);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_CEIL);
	}
}

void	parse_map_lines(char *line, char **buffer, t_cube *cube)
{
	static int	map_height = 0;
	static int	map_width = 0;

	if (is_valid_line(line, cube) > 1)
		exit_program(cube, 1, MULT_PLAYERS);
	buffer[map_height] = custom_strdup(line);
	if (buffer[map_height] == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	map_height++;
	if ((int)ft_strlen(line) > map_width)
		map_width = ft_strlen(line);
	cube->map.map_height = map_height;
	cube->map.map_width = map_width;
}

void	print_map_info(t_cube *cube)
{
	int	j;

	j = -1;
	printf("\t\tThe cube info is:\n");
	printf("\n\n\tThe map structure is:\n");
	while (cube->map.map[++j] != 0)
		printf("%s\n", cube->map.map[j]);
	j = -1;
	printf("\n\n\tThe map texture are is:\n");
	while (++j < cube->map.num_textures)
		printf("%s\n", cube->map.texture[j]);
	printf("\n\nThe floor colors are:\n");
	j = -1;
	while (++j < 3)
		printf("%d ", cube->map.floor_col[j]);
	j = -1;
	printf("\n\nThe ceiling colors are:\n");
	while (++j < 3)
		printf("%d ", cube->map.ceiling_col[j]);
	printf("\n\nPlayer's data are:\n");
	printf("player's x position: %f\n", cube->player.m_pos.x);
	printf("player's y position: %f\n", cube->player.m_pos.y);
	printf("\n\nmap_height: %d\n", cube->map.map_height);
	printf("\nmap_width: %d\n", cube->map.map_width);
}

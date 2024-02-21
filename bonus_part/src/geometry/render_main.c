/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:57:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/21 17:01:22 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_cube(t_cube *cube)
{
	allocate_text_pixels(cube);
	init_ray(&cube->player.ray);
	raycast_bonus(cube, &cube->player.ray);
	return (0);
}

int	render(t_cube *cube)
{
	keys_execute(cube);
	render_cube(cube);
	// render_minimap(cube);
	return (0);
}

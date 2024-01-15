/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/15 16:39:38 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include "../mlx/mlx.h"
// # include "gnl/get_next_line.h"

typedef struct s_cub 
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
	// t_img	*img;
	// t_point	*point;	
}			t_cub;

#endif
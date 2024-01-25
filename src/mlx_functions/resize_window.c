/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:38:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/01/25 16:43:38 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void update_dimensions(t_cube *cub, int flag)
{
    if (flag == EXPAND)
    {
        if (cub->screen.height > cub->screen.default_h - 1 
            || cub->screen.width > cub->screen.default_w - 1)
            return ;
        cub->screen.width *= 2;
        cub->screen.height *= 2;
    }
    else if (flag == REDUCE) 
    {
        if (cub->screen.height < 355 || cub->screen.width < 641)
            return ;
        cub->screen.width /= 2;
        cub->screen.height /= 2;
    }
}

static void create_new_window(t_cube *cub)
{
    void *new_mlx;
    void *new_win;

    new_mlx = mlx_init();
    new_win = mlx_new_window(new_mlx, cub->screen.width, cub->screen.height, "Cub3D");
    mlx_destroy_window(cub->screen.mlx, cub->screen.win);
    cub->screen.mlx = new_mlx;
    cub->screen.win = new_win;
}

static void hook_events(t_cube *cub)
{
    mlx_hook(cub->screen.win, 2, 0, key_press, cub);
    mlx_loop_hook(cub->screen.mlx, render, cub);
}

void resize_window(t_cube *cub, int flag)
{
    update_dimensions(cub, flag);
    create_new_window(cub);
    hook_events(cub);
}
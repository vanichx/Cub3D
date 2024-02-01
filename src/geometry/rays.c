// #include "cub3d.h"


// void render_static(t_cube *cube, int x, int drawStart, int drawEnd) {
//     // Determine the color of the wall based on the side
//     int wallColor = 0x00FFFFFF; // Default color (white)

//     // Adjust colors, textures, or shading based on the distance to create a 3D effect

//     // Draw the wall slice
//     for (int y = drawStart; y <= drawEnd; y++) {
//         mlx_pixel_put(cube->screen.mlx, cube->screen.win, x, y, wallColor);
//     }
// }

// void get_center_grid(t_cube *cube) {
//     cube->grid.center.x = cube->screen.width / 2;
//     cube->grid.center.y = cube->screen.height / 2;
// }

// // prepares the DDA variables necessary for the algorithm
// void prepare_DDA(t_cube *cube, t_vec ray_dir, int step[2], double sideDist[2])
// {
// 	// Calculate step and initial sideDist for the X direction
// 	if (ray_dir.dir[X] < 0)
// 	{
// 		step[X] = -1;
// 		sideDist[X] = (cube->player.m_pos.x - cube->player.pos.x) * (1 / ray_dir.dir[X]); 
// 	}
// 	else
// 	{
// 		step[X] = 1;
// 		sideDist[X] = (cube->player.pos.x + 1.0 - cube->player.m_pos.x) * (1 / ray_dir.dir[X]);
// 	}

// 	// Calculate step and initial sideDist for the Y direction
// 	if (ray_dir.dir[Y] < 0)
// 	{
// 		step[Y] = -1;
// 		sideDist[Y] = (cube->player.m_pos.y - cube->player.pos.y) * (1 / ray_dir.dir[Y]); 
// 	}
// 	else
// 	{
// 		step[Y] = 1;
// 		sideDist[Y] = (cube->player.pos.y + 1.0 - cube->player.m_pos.y) * (1 / ray_dir.dir[Y]);
// 	}
// }

// // performs the DDA algorithm
// double perform_DDA(t_cube *cube, t_vec ray_dir, int step[2], double sideDist[2])
// {
// 	int hit;
// 	int side; // variable to store which side of the wall was hit
// 	double deltaDist[2];
// 	double wall_dist;

// 	deltaDist[X] = fabs(1 / ray_dir.dir[X]);
// 	deltaDist[Y] = fabs(1 / ray_dir.dir[Y]);
// 	hit = 0; // initialise the hit flag to 0
// 	while (!hit)
// 	{
// 		// jump to the next map square, either in x-direction, or in y-direction
// 		if (sideDist[X] < sideDist[Y])
// 		{
// 			sideDist[X] += deltaDist[X];
// 			cube->player.m_pos.x += step[X];
// 			side = X; // record the Wall was hit on the x side
// 		}
// 		else
// 		{
// 			sideDist[Y] += deltaDist[Y];
// 			cube->player.m_pos.y += step[Y];
// 			side = Y; // record the Wall was hit on the y side
// 		}
// 		// Check if ray has hit a wall
// 		if (cube->map.map[(int)cube->player.m_pos.y][(int)cube->player.m_pos.x] == '1')
// 			hit = 1; // set the hit flag to true if a wall was hit
// 	}
// 	if (side == X)
// 		wall_dist = (cube->player.m_pos.x - cube->player.pos.x + (1 - step[X]) / 2) / ray_dir.dir[X];
// 	else
// 		wall_dist = (cube->player.m_pos.y - cube->player.pos.y + (1 - step[Y]) / 2) / ray_dir.dir[Y];
// 	return (wall_dist);
// }

// // casting the rays
// int cast_ray(t_cube *cube, t_vec ray_dir)
// {
// 	int step[2];
// 	double sideDist[2];
// 	double wall_dist;


// 	prepare_DDA(cube, ray_dir, step, sideDist);
// 	wall_dist = perform_DDA(cube, ray_dir, step, sideDist);
// 	return (wall_dist);
// }

// // renders the wall slice
// void render_wall_slice(t_cube *cube, int x, double wall_dist)
// {
// 	// calculate height of the wall slice on the screen
// 	int wall_height;
// 	int draw_start;
// 	int draw_end;
// 	void *img;

// 	if (cube->player.init_view == 'N')
// 		img = cube->grid.img_text[NO];
// 	else if (cube->player.init_view == 'S')
// 		img = cube->grid.img_text[SO];
// 	else if (cube->player.init_view == 'E')
// 		img = cube->grid.img_text[EA];
// 	else
// 		img = cube->grid.img_text[WE];
	
// 	wall_height = (int)(cube->screen.height / wall_dist);
// 	draw_start = cube->grid.center.y - wall_height / 2;
// 	draw_end = cube->grid.center.y + wall_height / 2;
// 	double tex_step = (double)64 / wall_height;
//     double tex_pos = 0.0;
// 	// clip drawing bounds to screen boundaries
// 	for (int y = draw_start; y <= draw_end; y++)
// 	{
// 		//calculate texture coordinate for this pixel
// 		int text_y = (int)tex_pos % 64;
// 		tex_pos += tex_step;
// 		mlx_pixel_put(cube->screen.mlx, cube->screen.win, x, y, 0x00FFFFFF);
// 	}
	
// }

// // the width and the height of the projection plane is the same as the resolution
// void	performRaycasting(t_cube *cube)
// {
// 	int front_length;
// 	t_vec ray_dir;
// 	int x;
// 	double wall_dist;
	
// 	x = 0;
// 	front_length = get_front_length(cube);
// 	get_center_grid(cube);
// 	cube->player.sub_angles = cube->player.fov / cube->screen.width;
// 	while (x < cube->screen.width)
// 	{
// 		ray_dir = find_casting_vec(cube, x);
// 		wall_dist = cast_ray(cube, ray_dir);
// 		render_wall_slice(cube, x, wall_dist);
// 		x++;
// 	}
// }



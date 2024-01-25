#include "cub3d.h"

#define FOV 60
#define RAY_ANGLE (FOV / cube->screen.width)

// void performRaycasting(t_cube *cube) {
//     for (int x = 0; x < cube->screen.width; x++) {
//         // Calculate ray position and direction
// 		t_vec rayDir;
// 		t_vec camera;
//         camera.dir[X] = 2 * x / (double)scube->screen.width - 1;
//         rayDir.dir[X] = cube->player.front.dir[X] + cube->player.cam.dir[X] * camera.dir[X];
//         rayDir.dir[Y] = cube->player.front.dir[Y] + cube->player->cam.dir[Y] * camera.dir[X];

//         // Length of ray from current position to next x or y-side
//         double sideDist[2], deltaDist[2];

//         // Length of ray from one x or y-side to next x or y-side
//         double deltaDist[X] = fabs(1 / rayDir.dir[X]);
//         double deltaDist[Y] = fabs(1 / rayDir.dir[Y]);

//         // Calculate step and initial sideDist
//         int step[2];
//         int hit = 0; // Was a wall hit?
//         int side;    // Was the wall hit on the x or y side?

//         if (rayDir.dir[X] < 0) {
//             step[X] = -1;
//             sideDist[X] = (cube->player.pos.x - cube->player.m_pos.x) * deltaDist[X];
//         } else {
//             step[X] = 1;
//             sideDist[X] = (cube->player.m_pos.x + 1.0 - cube->player.pos.x) * deltaDist[X];
//         }

//         if (rayDir[Y] < 0) {
//             step[Y] = -1;
//             sideDist[Y] = (cube->player.pos.y - cube->player.m_pos.y) * deltaDist[Y];
//         } else {
//             step[Y] = 1;
//             sideDist[Y] = (cube->player.m_pos.y + 1.0 - cube->player.pos.y) * deltaDist[Y];
//         }

//         // Perform DDA
//         while (!hit) {
//             // Jump to the next map square, either in x-direction or y-direction
//             if (sideDist[X] < sideDist[Y]) {
//                 sideDist[X] += deltaDist[X];
//                 cube->player.m_pos.x += step[X];
//                 side = 0;
//             } else {
//                 sideDist[Y] += deltaDist[Y];
//                 cube->player.m_pos.y += step[Y];
//                 side = 1;
//             }

//             // Check if ray has hit a wall
//             if (cube->map.map[cube->player.m_pos.x][cube->player.m_pos.y] == '1') {
//                 hit = 1;
//             }
//         }

//         // Calculate distance to the point of impact
//         double perpWallDist;
//         if (side == 0) {
//             perpWallDist = (cube->player.m_pos.x - cube->player.pos.x + (1 - step[X]) / 2) / rayDir[X];
//         } else {
//             perpWallDist = (cube->player.m_pos.y + (1 - step[Y]) / 2) / rayDir[Y];
//         }

//         // Calculate height of line to draw on screen
//         int lineHeight = (int)(cube->screen.height / perpWallDist);

//         // Calculate starting and ending points for drawing the wall slice
//         int drawStart = -lineHeight / 2 + cube->screen.height / 2;
//         if (drawStart < 0) {
//             drawStart = 0;
//         }
//         int drawEnd = lineHeight / 2 + cube->screen.height / 2;
//         if (drawEnd >= cube->screen.height) {
//             drawEnd = cube->screen.height - 1;
//         }

//         // Now, you can use the drawStart and drawEnd values to render the wall slice
//         // You may also use the 'side' variable to determine if the wall was hit on the x or y side
//         // Adjust colors, textures, or shading based on the distance to create a 3D effect
//     }
// }


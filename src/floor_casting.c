#include "../includes/cub3d.h"

// void set_floor_coords(t_data *data, int ray)
// {
//     float floorX = data->ply->posX + data->ray->distance * cos(data->ray->ray_ngl);
//     float floorY = data->ply->posY + data->ray->distance * sin(data->ray->ray_ngl);
//     data->ray->floorX = floorX;
//     data->ray->floorY = floorY;
// }

// void floor_casting(t_data *data, int x)
// {
//     int y;
//     float dis_player;
//     float rowDistance;

//     // Distance from the player to the projection plane
//     dis_player = (S_W / 2) / tan(FOV / 2 * DEG_TO_RAD);
//     y = S_H / 2;
//     while (y < S_H)
//     {
//         // Calculate distance from the player to this pixel row
//         rowDistance = dis_player / (y - S_H / 2.0f);
//         // Calculate world coordinates for the floor (floorX, floorY)
//         data->ray->floorX = data->ply->posX + rowDistance * cos(data->ray->ray_ngl);
//         data->ray->floorY = data->ply->posY + rowDistance * sin(data->ray->ray_ngl);
//         // Get texture coordinates
//         int texX = (int)(data->ray->floorX * 576) % 576;
//         int texY = (int)(data->ray->floorY * 576) % 576;
//         int color = get_pixel_from_texture(data->texture1, texX, texY);
//         ft_pixel_put(data, x, y, color);

//         y++;
//     }
// }
// void sky_casting(t_data *data, int x)
// {
//     int y;
//     float dis_player;

//     // Distance from the player to the projection plane
//     dis_player = (S_W / 2) / tan(FOV / 2 * DEG_TO_RAD);
//     y = 0;
//     while (y < S_H)
//     {
//         // Calculate distance from the player to this pixel row
//         float rowDistance = dis_player / (y - S_H / 2.0f);

//         // Calculate world coordinates for the floor (floorX, floorY)
//         float floorX = data->ply->posX + rowDistance * cos(data->ray->ray_ngl);
//         float floorY = data->ply->posY + rowDistance * sin(data->ray->ray_ngl);

//         // Get texture coordinates
//         int texX = (int)(floorX * 1000) % 1000;
//         int texY = (int)(floorY * 1000) % 1000;

//         // Get the color from the texture and apply to the pixel
//         int color = get_pixel_from_texture(data->texture2, texX, texY);
//         ft_pixel_put(data, x, y, color);

//         y++;
//     }
// }

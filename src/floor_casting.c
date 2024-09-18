#include "../includes/cub3d.h"

void set_floor_coords(t_data *data, int ray)
{
    float floorX = data->ply->posX + data->ray->distance * cos(data->ray->ray_ngl);
    float floorY = data->ply->posY + data->ray->distance * sin(data->ray->ray_ngl);
    data->ray->floorX = floorX;
    data->ray->floorY = floorY;
}

void floor_casting(t_data *data, int x)
{
    int y;
    float dis_player = (S_W / 2) / tan(FOV / 2 * DEG_TO_RAD);
    data->ply->angle = normalize_angle(data->ply->angle);
    double rayDirX0 = cos(data->ply->angle - FOV / 2 * DEG_TO_RAD);
    double rayDirX1 = cos(data->ply->angle + FOV / 2 * DEG_TO_RAD);
    double rayDirY0 = sin(data->ply->angle - FOV / 2 * DEG_TO_RAD);
    double rayDirY1 = sin(data->ply->angle + FOV / 2 * DEG_TO_RAD);
    
    for (y = S_H / 2 + data->ply->look_offset; y < S_H; y++) {
        double rowDistance = dis_player / (y - S_H / 2 - data->ply->look_offset);
        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / S_W;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / S_W;
        
        double floorX = data->ply->posX + rowDistance * rayDirX0;
        double floorY = data->ply->posY + rowDistance * rayDirY0;
        if (y > S_H / 2 + data->ply->look_offset)
        {
            for (x = 0; x < S_W; x++) {
            int texX = (int)(floorX * 576) % 576;  // Assuming 64x64 textures
            int texY = (int)(floorY * 576) % 576;
            // int color = get_pixel_from_texture(data->texture2, texX, texY);
            int color = 3933954;

            // Apply brightness factor based on distance
            float brightness_factor = fmax(1.0 - (rowDistance * 0.1), 0.3);
            int r = ((color >> 16) & 0xFF) * brightness_factor;
            int g = ((color >> 8) & 0xFF) * brightness_factor;
            int b = (color & 0xFF) * brightness_factor;
            color = (r << 16) | (g << 8) | b;
            
            ft_pixel_put(data, x, y, color);

            floorX += floorStepX;
            floorY += floorStepY;
            }
        }
    }
}


void sky_casting(t_data *data, int x)
{
    int y;
    float dis_player;

    // Distance from the player to the projection plane
    dis_player = (S_W / 2) / tan(FOV / 2 * DEG_TO_RAD);
    y = 0;
    while (y < S_H)
    {
        // Calculate distance from the player to this pixel row
        float rowDistance = dis_player / (y - S_H / 2.0f);

        // Calculate world coordinates for the floor (floorX, floorY)
        float floorX = data->ply->posX + rowDistance * cos(data->ray->ray_ngl);
        float floorY = data->ply->posY + rowDistance * sin(data->ray->ray_ngl);

        // Get texture coordinates
        int texX = (int)(floorX * 1000) % 1000;
        int texY = (int)(floorY * 1000) % 1000;

        // Get the color from the texture and apply to the pixel
        int color = get_pixel_from_texture(data->texture2, texX, texY);
        ft_pixel_put(data, x, y, color);

        y++;
    }
}

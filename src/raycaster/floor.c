#include "../../includes/raycaster.h"

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

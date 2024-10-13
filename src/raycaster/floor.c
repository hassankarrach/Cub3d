#include "../../includes/raycaster.h"

void floor_casting(t_data *data, int x)
{
    int y;
    int color;
    float dis_player = (S_H / 2) / tan(FOV / 2 * DEG_TO_RAD);

    for (y = S_H / 2 + data->ply->look_offset; y < S_H; y++) {
        double rowDistance = dis_player / (y - S_H / 2 - data->ply->look_offset);
        if (y > S_H / 2 + data->ply->look_offset)
        {
            for (x = 0; x < S_H; x++) {
            float brightness_factor = 1.0 - (rowDistance * 0.1);
            int r = (data->args->Floor_color.r) * brightness_factor;
            r = clamp(r, 0, 255);
            int g = (data->args->Floor_color.g) * brightness_factor;
            g = clamp(g, 0, 255);
            int b = (data->args->Floor_color.b) * brightness_factor;
            b = clamp(b, 0, 255);
            color = (r << 16) | (g << 8) | b;
            ft_pixel_put(data, x, y, color);
            }
        }
    }
}

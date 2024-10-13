#include "../../includes/renderer.h"

void draw_player(t_data *data, double current_time)
{
    int start_y;
    int x;
    int y;
    int color;
    static int frame;
    static int last_update_time;
    double time_between_frames = 0;

    x = 0;
    start_y = S_H - data->textures.player[0]->height + data->ply->look_offset;
    if (start_y < S_H - data->textures.player[0]->height)
        start_y = S_H - data->textures.player[0]->height;
    y = start_y;
    if (current_time - last_update_time >= time_between_frames)
    {
        if (frame < 25)
            frame++;
        else
            frame = 0;
    }
    while (y < S_H)
    {
        x = 0;
        while (x < S_W)
        {
            color = get_pixel_from_texture(data->textures.player[frame], x, y - start_y);
            if (color != BLK && color)
                ft_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    last_update_time = current_time;
}
#include "../includes/cub3d.h"

static int pos_to_color(t_data *data, int x, int y)
{
    int start_x, start_y;
    int map_x, map_y;

    start_x = (data->ply->posX / TILE_SIZE) * 32 - ((S_W_MINI_MAP / 2));
    start_y = (data->ply->posY / TILE_SIZE) * 32 - ((S_H_MINI_MAP / 2));
    x += start_x;
    y += start_y;
    map_x = (int)(x / 32);
    map_y = (int)(y / 32);
    if (y < 0 || x < 0)
        return (0);

    if (map_x < 0 || map_x > data->w_map || map_y < 0 || map_y > data->h_map)
        return 0;
    if (data->map2d[map_y][map_x] == '1')
        return BLU; // Wall
    else
        return 0; // Empty space
}
void set_pixels_img(t_data *data)
{
    int x;
    int y;
    int color;

    x = 0;
    y = 0;
    while (x < 350)
    {
        y = 0;
        while (y < 267)
        {
            color = get_pixel_from_texture(data->mini_map2, x, y);
            if (color != BLK)
                ft_pixel_put(data, x, y, color);
            y++;
        }
        x++;
    }
}
static int adjust_color_opacity(int color, float fade_factor)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    // Apply fade factor to RGB components
    r = (int)(r * fade_factor);
    g = (int)(g * fade_factor);
    b = (int)(b * fade_factor);

    // Recombine the faded color
    return (r << 16) | (g << 8) | b;
}

void render_mini_map(t_data *data)
{
    int x, y;

    set_pixels_img(data);
    for (x = 20; x < S_W_MINI_MAP; x++)
    {
        for (y = 18; y < S_H_MINI_MAP; y++)
        {
            int color = pos_to_color(data, x, y);
            if (color == 0)
                continue;

            // Calculate distance from the center
            float distance = sqrt(pow(x - S_W_MINI_MAP / 2, 2) + pow(y - S_H_MINI_MAP / 2, 2));

            // Normalize the distance and get fade factor
            float max_distance = sqrt(pow(S_W_MINI_MAP / 2, 2) + pow(S_H_MINI_MAP / 2, 2));
            float fade_factor = 1.0 - (distance / max_distance); // Closer to the center -> less fading

            // Adjust the color based on fade factor
            int faded_color = adjust_color_opacity(color, fade_factor);

            // Put the pixel with the faded color
                ft_pixel_put(data, x, y, faded_color);
        }
    }

    ft_pixel_put(data, S_W_MINI_MAP / 2, S_H_MINI_MAP / 2, RED);

    // printf("color : %d\n", pos_to_color(data, 60, 60));
}

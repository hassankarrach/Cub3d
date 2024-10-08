#include "../includes/cub3d.h"

static int pos_to_color(t_data *data, int x, int y)
{
    float relative_x, relative_y;
    int map_x, map_y;
    
    float player_x = (data->ply->posX / TILE_SIZE) * 32;
    float player_y = (data->ply->posY / TILE_SIZE) * 32;
    relative_x = x - (S_W_MINI_MAP / 2);
    relative_y = y - (S_H_MINI_MAP / 2);
    float rotated_x = cos(data->ply->angle + M_PI / 2) * relative_x - sin(data->ply->angle + M_PI / 2) * relative_y + player_x;
    float rotated_y = sin(data->ply->angle + M_PI / 2) * relative_x + cos(data->ply->angle + M_PI / 2) * relative_y + player_y;
    
    map_x = (int)(rotated_x / 32);
    map_y = (int)(rotated_y / 32);
    if (map_x < 0 || map_x > data->w_map || map_y < 0 || map_y > data->h_map || rotated_x < 0 || rotated_y < 0)
        return -1;
    if (data->map2d[map_y][map_x] == '1')
        return MAP_CLR;  // Wall
    if (data->map2d[map_y][map_x] == 'D')
        return ORNG;  // Wall
    if (data->map2d[map_y][map_x] == 'O')
        return GREN;
    else
        return -1;  // Empty space
}

void draw_player_icon(t_data *data)
{
    int x;
    int y;
    int start_x;
    int start_y;
    int color;

    start_x = ((S_W_MINI_MAP + 16) / 2) - (32 / 2);
    start_y = ((S_H_MINI_MAP + 14) / 2) - (32 / 2);
    x = 0;
    y = 0;
    while (y < data->icon_player->height)
    {
        x = 0;
        while (x < data->icon_player->width)
        {
                color = get_pixel_from_texture(data->icon_player, x, y);
                if (color != BLK)
                    ft_pixel_put(data, x + start_x, y + start_y, color);
            x++;
        }
        y++;
    }
}
void set_pixels_img(t_data *data)
{
    int x;
    int y;
    int color;

    x = 0;
    y = 0;
    while (x < S_W_MINI_MAP + 14)
    {
        y = 0;
        while (y < S_H_MINI_MAP + 14)
        {
            color = get_pixel_from_texture(data->mini_map, x, y);
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

    r = (int)(r * fade_factor);
    g = (int)(g * fade_factor);
    b = (int)(b * fade_factor);
    return (r << 16) | (g << 8) | b;
}

void render_mini_map(t_data *data)
{
    int x, y;
    
    set_pixels_img(data);
    for (x = 16; x < S_W_MINI_MAP; x++)
    {
        for (y = 14; y < S_H_MINI_MAP; y++)
        {
            int color = pos_to_color(data, x, y);
            if (color == -1)
                continue;
            float distance = sqrt(pow(x - S_W_MINI_MAP / 2, 2) + pow(y - S_H_MINI_MAP / 2, 2));
            float max_distance = sqrt(pow(S_W_MINI_MAP / 2, 2) + pow(S_H_MINI_MAP / 2, 2));
            float fade_factor = 1.0 - (distance / max_distance * 0.5);
            int faded_color = adjust_color_opacity(color, fade_factor);
            ft_pixel_put(data, x, y, faded_color);
        }
    }
    draw_player_icon(data);
}

// render the scene here.
#include "../includes/cub3d.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
}
void draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(data, x0, y0, 0xFFFFFF); // Set the pixel color as white

        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_player(t_data *data)
{
    int i;
    int j;
    int radius = 2;
    int centerX = (data->ply->posX * 11) + 5;
    int centerY = (data->ply->posY * 11) + 5;
    i = -radius;
    while (i <= radius)
    {
        j = -radius;
        while (j <= radius)
        {
            if (i * i + j * j <= radius * radius)
            {
                my_mlx_pixel_put(data, centerX + j, centerY + i, 0x0000FF00); // Green for player
            }
            j++;
        }
        i++;
    }
    draw_line(data, centerX, centerY, centerX + 10 * cos(data->ply->angle), centerY + 10 * sin(data->ply->angle));
}
void draw_tile(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            my_mlx_pixel_put(data, x * 11 + j, y * 11 + i, color);
            j++;
        }
        i++;
    }
}
void render_mini_map(t_data *data, char **map)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (map[y] && y < 20)
    {
        x = 0;
        while (map[y][x] && x < 20)
        {
            if (map[y][x] == '1')
            {
                draw_tile(data, x, y, BLK);
            }
            x++;
        }
        y++;
    }
    draw_player(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}

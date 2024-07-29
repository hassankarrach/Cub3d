// render the scene here.
#include "../includes/cub3d.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
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

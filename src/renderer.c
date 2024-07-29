// render the scene here.
#include "../includes/cub3d.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
}

void draw_tile(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            mlx_pixel_put(data->mlx->mlx, data->mlx->win, x * 33 + j, y * 33 + i, color);
            j++;
        }
        i++;
    }
}
void render_mini_map(t_data *data, char **map)
{
    int y;
    int x;

    x = 0;
    y = 0;
    while (map[y] && y < S_H_MINI_MAP)
    {
        x = 0;
        while (map[y][x] && x < S_W_MINI_MAP)
        {
            if (map[y][x] == '1')
            {
                draw_tile(data, x, y, BLK);
            }
            else
            {
                draw_tile(data, x, y, BLU);
            }
            x++;
        }
        y++;
    }
}

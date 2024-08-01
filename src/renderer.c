// render the scene here.
#include "../includes/cub3d.h"
static void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
}

static void draw_player(t_data *data)
{
    int x;
    int y;
    int i;
    int j;

    x = (S_W - 250) + 125;
    y = (S_H - 150) + 75;
    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            ft_pixel_put(data, x + i, y + j, BLU);
            j++;
        }
        i++;
    }
}

void render_mini_map(t_data *data, char **map)
{
    int startX;
    int startY;

    // int curr_x;
    // int curr_y;

    (void)map;
    startX = S_W - 250;
    startY = S_H - 150;

    while (startY <= S_H)
    {
        startX = S_W - 250;
        while (startX <= S_W)
        {
            ft_pixel_put(data, startX, startY, 0x00FF0000);
            startX++;
        }
        startY++;
    }
    draw_player(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}

// render the scene here.
#include "../includes/cub3d.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
}

void render_mini_map(void *mlx, void *win, char **map, t_player *player)
{
    (void)player;
    // (void)mlx;
    // (void)win;
    // (void)map;
    int y;
    int x;
    int i;
    int j;

    i = 0;
    j = 0;
    x = 0;
    y = 0;
    while (map[y] && y < S_H_MINI_MAP)
    {
        x = 0;
        while  (map[y][x] && x < S_W_MINI_MAP)
        {
            if (map[y][x] == '1')
            {
                i = 0;
                while (i < 10)
                {
                    j = 0;
                    while (j < 10)
                    {
                        mlx_pixel_put(mlx, win, x * 10 + j, y * 10 + i, BLU);
                        j++;
                    }
                    mlx_pixel_put(mlx, win, x * 11 + j, y * 11 + i, WHI);
                    i++;
                }
            }
            else
            {
                i = 0;
                while (i < 10)
                {
                    j = 0;
                    while (j < 10)
                    {
                        mlx_pixel_put(mlx, win, x * 10 + j, y * 10 + i, ORNG);
                        j++;
                    }
                    i++;
                }
            }
            x++;
        }
        y++;
    }
}

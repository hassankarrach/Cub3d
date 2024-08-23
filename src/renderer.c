// render the scene here.
#include "../includes/cub3d.h"
static void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(int *)dst = color;
}
int check_out_of_bounds(t_data *data, int x, int y)
{
    int i;
    int j;

    i = floor(x / 32);
    j = floor(y / 32);
    if (i < 0 || i >= S_W || j < 0 || j >= S_H) // out of bounds
        return (-2);
    if (data->args->map_lines[j][i] == '1') // wall
        return (1);
    else if (data->args->map_lines[j][i] == '0' || data->args->map_lines[j][i] == 'W') // empty space
        return (-1);
    return (0); // player position
}
void draw_player(t_data *data)
{
    int centerX = (data->ply->posX);
    int centerY = (data->ply->posY);

    int height = 8;
    int halfWidth = 5;
    int i;

    i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = -y; x <= y; x++)
            ft_pixel_put(data, centerX + x, centerY + y, RED);
    }
    while (i < 15)
    {
        ft_pixel_put(data, centerX + i, centerY + i, RED);
        i++;
    }
}

void draw_2d_game(t_data *data)
{
    int i;
    int j;
    int check;

    i = 0;
    j = 0;
    check = 0;
    while (j < S_H)
    {
        i = 0;
        while (i < S_W)
        {
            check = check_out_of_bounds(data, i, j);
            if (check == 1)
            {
                if (i % 32 == 0 || j % 32 == 0)
                    ft_pixel_put(data, i, j, BLK);
                else
                    ft_pixel_put(data, i, j, BLU);
            }
            else if (check == -1)
                ft_pixel_put(data, i, j, ORNG);
            i++;
        }
        j++;
    }
    draw_player(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
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

    i = x / TILE_SIZE;
    j = y / TILE_SIZE;
    if (i < 0 || i >= data->w_map || j < 0 || j >= data->h_map)
        return (1);
    if (data->args->map_lines[j][i] == '1')
        return (1);
    else if (data->args->map_lines[j][i] == '0')
        return (-1);
    return (0);
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

int scaling_i_j(t_data *data, int i, int j)
{
    int x;
    int y;

    x = j - 950;
    y = i - 450;
    return (check_out_of_bounds(data, x, y));
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

    while (startY < S_H)
    {
        startX = S_W - 250;
        while (startX < S_W)
        {
            if (scaling_i_j(data, startY, startX) == 1)
                ft_pixel_put(data, startX, startY, RED);
            else if (scaling_i_j(data, startY, startX) == -1)
                ft_pixel_put(data, startX, startY, WHI);

            startX++;
        }
        startY++;
    }
    draw_player(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}

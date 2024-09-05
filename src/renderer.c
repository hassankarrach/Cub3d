// render the scene here.
#include "../includes/cub3d.h"
static void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
    if (x >= 0 && x < S_W && y >= 0 && y < S_H)
	    *(int *)dst = color;
}
int check_out_of_bounds(t_data *data, int x, int y)
{
    int i;
    int j;

    i = floor(x / 32);
    j = floor(y / 32);
    if (i < 0 || x >= S_W || j < 0 || y >= S_H) // out of bounds
        return (-2);
    if (data->args->map_lines[j][i] == '1') // wall
        return (1);
    else if (data->args->map_lines[j][i] == '0' || data->args->map_lines[j][i] == 'N') // empty space
        return (-1);
    return (0); // player positionft/ft_strlen.o ./lib/libft/ft_strncmp.o ./lib/libft/ft_strrchr.o ./lib/libft/ft_strlcpy.o ./lib/libft/ft_substr
}
void draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        ft_pixel_put(data, x0, y0, GREN);

        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_player(t_data *data)
{
    int x_start;
    int y_start;
    int end_x;
    int end_y;

    x_start = data->ply->posX - 2;
    y_start = data->ply->posY - 2;
    end_x = x_start + 4;
    end_y = y_start + 4;
    while (y_start < end_y)
    {
        x_start = data->ply->posX - 2;
        while (x_start < end_x)
        {
            ft_pixel_put(data, x_start, y_start, RED);
            x_start++;
        }
        y_start++;
    }
    // int rayLength = 16;
    // int endX = data->ply->posX + cos(data->ply->angle) * rayLength;
    // int endY = data->ply->posY + sin(data->ply->angle) * rayLength;
    // draw_line(data, data->ply->posX, data->ply->posY, endX, endY);
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
                    ft_pixel_put(data, i, j, BLU);
            else if (check == -1)
                ft_pixel_put(data, i, j, ORNG);
            if (i % 32 == 0 || j % 32 == 0)
                ft_pixel_put(data, i, j, BLK);
            i++;
        }
        j++;
    }
    draw_player(data);
    raycasting(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
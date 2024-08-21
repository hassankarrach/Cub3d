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

    i = floor(x / 20);
    j = floor(y / 20);
    if (i < 0 || i >= data->w_map || j < 0 || j >= data->h_map) // out of bounds
        return (-2);
    if (data->args->map_lines[j][i] == '1') // wall
        return (1);
    else if (data->args->map_lines[j][i] == '0') // empty space
        return (-1);
    return (0); // player position
}

// static void draw_player(t_data *data)
// {
//     (void)data;
// }
void render_mini_map(t_data *data, char **map)
{
    int startX;
    int startY;

    // mini_map
    int mini_map_height = 150;
    int mini_map_width = 250;
    // mini_map height and width in pixels
    int mini_map_el_size = 20;

    // available space
    float x_space = (mini_map_width - mini_map_el_size) / 2;
    float y_space = (mini_map_height - mini_map_el_size) / 2;

    // Player position
    int player_x = (data->index_x) * mini_map_el_size;
    int player_y = (data->index_y) * mini_map_el_size;
    // printf("player x: %d\n", (data->index_x));
    // printf("player y: %d\n", (data->index_y));

    // map start position
    int map_start_x = (player_x - x_space);
    int map_start_y = (player_y - y_space);
    // sleep (2000);

    // printf("player x: %d\n", player_x);
    // printf("player y: %d\n", player_y);

    // printf("x space: %d\n", x_space);
    // printf("y space: %d\n", y_space);

    // printf("map start x: %d\n", map_start_x);
    // printf("map start y: %d\n", map_start_y);

    (void)map;
    startX = 0;
    startY = 0;

while (startY < mini_map_height)
{
    startX = 0;
    while (startX < mini_map_width)
    {
        if (startX == 0 || startX == mini_map_width - 1 || startY == 0 || startY == mini_map_height - 1) // 
            ft_pixel_put(data, startX, startY, ORNG);
        else
        {
            int check = check_out_of_bounds(data, map_start_x, map_start_y);
            if (check == 1)
                ft_pixel_put(data, startX, startY, BLU);
            else if (check == -1)
                ft_pixel_put(data, startX, startY, BLK);
        }
        startX++;
        map_start_x++;
    }
    map_start_x = player_x - x_space;
    map_start_y++;
    startY++;
}

    // draw_player(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}

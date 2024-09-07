// Entry point of the program.
#include "../includes/cub3d.h"
static int game_loop(void *arg)
{
    t_data *data = (t_data *)arg;
    mlx_clear_window(data->mlx->mlx, data->mlx->win);
    // draw_2d_game(data);
    raycasting(data);
    drawing_3d_game(data);

    // draw_sky_floor(data);
    return (0);
}

int main(int ac, char **av)
{
    t_args cub3d_args;
    t_data data;


    parser(ac, av, &cub3d_args);
    init_game(&data, &cub3d_args);
    handle_events(&data);

    data.texture1 = texture_loader(&data, "./assets/textures/texture2.xpm");

    mlx_loop_hook(data.mlx->mlx, game_loop, &data);

    mlx_loop(data.mlx->mlx);
    return (0);
}
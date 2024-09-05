// Entry point of the program.
#include "../includes/cub3d.h"
static int game_loop(void *arg)
{
    t_data *data = (t_data *)arg;
    mlx_clear_window(data->mlx->mlx, data->mlx->win);
    // update_player(data->ply);
    draw_2d_game(data);
    // raycasting(data);
    // render_mini_map(data, data->map2d);
    return (0);
}

int main(int ac, char **av)
{
    t_args  cub3d_args;
    t_data  data;

    parser(ac, av, &cub3d_args);
    init_game(&data, &cub3d_args);
    handle_events(&data);
    //mlx 
    mlx_loop_hook(data.mlx->mlx, game_loop, &data);
    // render_mini_map(&data, data.map2d);
    // draw_2d_game(&data);
    mlx_loop(data.mlx->mlx);
    return (0);
}
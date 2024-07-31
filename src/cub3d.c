// Entry point of the program.
#include "../includes/cub3d.h"
void update(t_data *data)
{
    mlx_clear_window(data->mlx->mlx, data->mlx->win);
    // raycasting(data);
    render_mini_map(data, data->map2d);
}
int main(int ac, char **av)
{
    t_args  cub3d_args;
    t_data  data;

    parser(ac, av, &cub3d_args);
    init_game(&data, &cub3d_args);
    handle_events(&data);
    update(&data);
    handle_events(&data);
    
    mlx_loop(data.mlx->mlx);
    return (0);
}
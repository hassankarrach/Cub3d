// Entry point of the program.
#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_args  cub3d_args;
    t_data  data;

    parser(ac, av, &cub3d_args);
    init_game(&data, &cub3d_args);
    handle_events(&data);
    // raycasting(&data);
    render_mini_map(&data, data.map2d); // test
    mlx_loop(data.mlx->mlx);
    return (0);
}
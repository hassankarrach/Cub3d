// Entry point of the program.
#include "../includes/cub3d.h"
void update_player(t_player *player)
{
    player->angle += player->turn_direction * ROTATION_SPEED;
    player->angle = normalize_angle(player->angle);
    player->posX += player->walk_direction * MOVE_SPEED * cos(player->angle);
    player->posY += player->walk_direction * MOVE_SPEED * sin(player->angle);
}
static int game_loop(void *arg)
{
    t_data *data = (t_data *)arg;
    mlx_clear_window(data->mlx->mlx, data->mlx->win);
    render_mini_map(data, data->map2d);
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
    // mlx_loop_hook(data.mlx->mlx, game_loop, &data);
        render_mini_map(&data, data.map2d);
    mlx_loop(data.mlx->mlx);
    return (0);
}
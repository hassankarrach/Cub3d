// Entry point of the program.
#include "../includes/cub3d.h"
void update_player(t_player *player)
{
    player->posX += cos(player->angle) * player->walk_direction * MOVE_SPEED; // walk_direction is negative when walking back and positive when walking forward
    player->posY += sin(player->angle) * player->walk_direction * MOVE_SPEED;
    player->angle += player->turn_direction * ROTATION_SPEED; // turn_left is negative when turning left and positive when turning right
    printf ("%f %f %f\n", player->posX, player->posY, player->angle);
}
int update(void *arg)
{
    t_data *data = (t_data *)arg;
    mlx_clear_window(data->mlx->mlx, data->mlx->win);
    update_player(data->ply);
    // raycasting(data);
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
    update(&data);
    mlx_loop_hook(data.mlx->mlx, update, &data);
    mlx_loop(data.mlx->mlx);
    return (0);
}
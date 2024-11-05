#include "../includes/cub3d.h"

static int game_loop(void *arg)
{
    static int i = 0;
    static double bobbing_time = 0;
    double	time_between_frames;
    static double last_update_time;
    time_between_frames = 0.02;
    t_data *data = (t_data *)arg;

    double current_time = get_time_in_seconds();

    if (data->state == LOBBY)
        lobby(data);
    else if (data->state == PAUSED)
        game_pause(data);
    else
    {
        mlx_clear_window(data->mlx->mlx, data->mlx->win);
        if (!data->ply->walk_direction)
        {
            if (current_time - data->last_update_time >= time_between_frames)
            {
                bobbing_time += 0.08;
                data->ply->look_offset += sin(bobbing_time) * 3;
                data->last_update_time = current_time;
            }
        }
        draw_sky_floor(data);
        floor_casting(data, 0);
        raycasting(data);
        render_mini_map(data);
        update_door_status(data, current_time);
        update_ply_animation(data, data->ply, current_time);
        update_player(data->ply, data);
        draw_player(data, current_time);
        drawing_3d_game(data);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_args cub3d_args;
    t_data data;

    parser(ac, av, &cub3d_args);

    init_game(&data, &cub3d_args);
    handle_events(&data);
    int i;

    i = 0;
    while (data.args->map_lines[i])
        printf("%s\n", data.args->map_lines[i++]);
    mlx_loop_hook(data.mlx->mlx, game_loop, &data);

    mlx_loop(data.mlx->mlx);
    return (0);
}

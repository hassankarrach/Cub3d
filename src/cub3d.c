#include "../includes/cub3d.h"

static int game_loop(void *arg)
{
    static int i = 0;
    static double bobbing_time = 0;
    t_data *data = (t_data *)arg;

    double current_time = get_time_in_seconds();

    if (data->state == LOBBY)
        lobby(data);
    else if (data->state == DEAD)
        you_died(data);
    else if (data->state == PAUSED)
        game_pause(data);
    else
    {
        if (!data->sounds[1].is_playing)
        {
            // stop_all_sounds(data);
            // play_sound(&data->sounds[1]);
        }
        mlx_clear_window(data->mlx->mlx, data->mlx->win);
        if (!data->ply->walk_direction)
        {
            bobbing_time += 0.1;
            data->ply->look_offset += sin(bobbing_time) * 2;
        }
        draw_sky_floor(data);
        floor_casting(data, 0);
        update_player(data->ply, data);
        raycasting(data);
        update_door_animation(data, data->door, current_time);
        render_mini_map(data);
        draw_player(data, current_time);
        drawing_3d_game(data);
    }
    // draw_sky_floor(data);

    return (0);
}

int main(int ac, char **av)
{
    t_args cub3d_args;
    t_data data;

    parser(ac, av, &cub3d_args);

    // init_game(&data, &cub3d_args);
    
    // handle_events(&data);

    // mlx_loop_hook(data.mlx->mlx, game_loop, &data);

    // mlx_loop(data.mlx->mlx);
    return (0);
}
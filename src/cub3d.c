// Entry point of the program.
#include "../includes/cub3d.h"
double get_time_in_seconds(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec + (time.tv_usec / 1000000.0));
}

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
        render_mini_map(data);
        drawing_3d_game(data);
        update_door_animation(data, data->door, current_time);
    }
    // draw_sky_floor(data);

    return (0);
}

int main(int ac, char **av)
{
    t_args cub3d_args;
    t_data data;
    t_sprite sprite;

    parser(ac, av, &cub3d_args);
    init_game(&data, &cub3d_args);
    handle_events(&data);
    // mlx_mouse_hide(data.mlx->mlx, data.mlx->win);
    mlx_mouse_move(data.mlx->mlx, data.mlx->win, S_W / 2, S_H / 2);
    sprite.x = TILE_SIZE * 11 + TILE_SIZE / 2;
    sprite.y = TILE_SIZE * 8 + TILE_SIZE / 2;
    data.sprites = &sprite;
    sprite.texture = texture_loader(&data, "./assets/textures/texture.xpm");
    data.texture1 = texture_loader(&data, "./assets/textures/texture1.xpm");
    data.texture2 = texture_loader(&data, "./assets/textures/texture2.xpm");
    data.texture3 = texture_loader(&data, "./assets/textures/texture3.xpm");
    data.texture4 = texture_loader(&data, "./assets/textures/texture4.xpm");
    data.texture_art1 = texture_loader(&data, "./assets/textures/wall_with_frame.xpm");
    data.texture_art2 = texture_loader(&data, "./assets/textures/wall_with_frame2.xpm");
    data.mini_map = texture_loader(&data, "./assets/mini_map.xpm");
    data.icon_player = texture_loader(&data, "./assets/player_icon.xpm");
    data.logo = texture_loader(&data, "./assets/logo.xpm");
    data.press_to_start = texture_loader(&data, "./assets/press_space.xpm");
    data.you_died = texture_loader(&data, "./assets/you_died.xpm");
    mlx_loop_hook(data.mlx->mlx, game_loop, &data);

    // test

    mlx_loop(data.mlx->mlx);
    return (0);
}
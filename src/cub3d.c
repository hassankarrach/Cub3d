// Entry point of the program.
#include "../includes/cub3d.h"

static int game_loop(void *arg)
{
    static int i = 0;
    static double bobbing_time = 0;
    t_data *data = (t_data *)arg;
    // draw_2d_game(data);
    // if (data->state == LOBBY)
    //     lobby(data);
    // else if (data->state == DEAD)
    //     you_died(data);
    // else if (data->state == PAUSED)
    //     game_pause(data);
    // else
    // {
        if (!data->sounds[1].is_playing)
        {
            stop_all_sounds(data);
            play_sound(&data->sounds[1]);
        }
        mlx_clear_window(data->mlx->mlx, data->mlx->win);
        if (!data->ply->walk_direction)
        {
            bobbing_time += 0.1;
            data->ply->look_offset += sin(bobbing_time) * 2;
        }
        raycasting(data);
        drawing_3d_game(data);
        render_mini_map(data);
    // }
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
    mlx_mouse_move(data.mlx->mlx, data.mlx->win, S_W / 2, S_H / 2);
    sprite.x = TILE_SIZE * 8 + TILE_SIZE / 2;
    sprite.y = TILE_SIZE * 10 + TILE_SIZE / 2;
    data.sprites = &sprite;
    data.texture1 = texture_loader(&data, "./assets/textures/texture1.xpm");
    data.texture2 = texture_loader(&data, "./assets/textures/texture2.xpm");
    data.texture3 = texture_loader(&data, "./assets/textures/texture3.xpm");
    data.texture4 = texture_loader(&data, "./assets/textures/texture4.xpm");
    data.player[0] = texture_loader(&data, "./assets/foreground/1.xpm");
    data.player[1] = texture_loader(&data, "./assets/foreground/2.xpm");
    data.player[2] = texture_loader(&data, "./assets/foreground/3.xpm");
    data.player[3] = texture_loader(&data, "./assets/foreground/4.xpm");
    data.player[4] = texture_loader(&data, "./assets/foreground/5.xpm");
    data.player[5] = texture_loader(&data, "./assets/foreground/6.xpm");
    data.player[6] = texture_loader(&data, "./assets/foreground/7.xpm");
    data.player[7] = texture_loader(&data, "./assets/foreground/8.xpm");
    data.player[8] = texture_loader(&data, "./assets/foreground/9.xpm");
    data.player[9] = texture_loader(&data, "./assets/foreground/10.xpm");
    data.player[10] = texture_loader(&data, "./assets/foreground/11.xpm");
    data.player[11] = texture_loader(&data, "./assets/foreground/12.xpm");
    data.player[12] = texture_loader(&data, "./assets/foreground/13.xpm");
    data.player[13] = texture_loader(&data, "./assets/foreground/14.xpm");
    data.logo = texture_loader(&data, "./assets/logo.xpm");
    data.press_to_start = texture_loader(&data, "./assets/press_space.xpm");
    data.you_died = texture_loader(&data, "./assets/you_died.xpm");

    mlx_loop_hook(data.mlx->mlx, game_loop, &data);

    // test

    mlx_loop(data.mlx->mlx);
    return (0);
}
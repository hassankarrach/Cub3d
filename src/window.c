#include "../includes/cub3d.h"

void handle_events(t_data *data)
{
    mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
    mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
    mlx_hook(data->mlx->win, 4, 1L << 2, mouse_release, data);
    mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
    mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ON_KEYUP || keycode == 102)
        data->ply->walk_direction = 1;
    if (keycode == ON_KEYDOWN)
        data->ply->walk_direction = -1;
    if (keycode == ON_TURN_LEFT)
        data->ply->turn_direction = -1;
    if (keycode == ON_TURN_RIGHT)
        data->ply->turn_direction = 1;
    if (keycode == 102)
        data->ply->move_speed = 2;
    if (keycode == 32)
        data->state = PLAYING;
    update_player(data->ply, data);
    return 0;
}
int mouse_move(int x, int y, t_data *data)
{
    static int last_x = 0;
    static int last_y = S_W / 2;
    int mouse_delta_x = x - last_x;
    int mouse_delta_y = y - last_y;
    last_x = x;
    last_y = y;
    data->ply->angle += mouse_delta_x * (ROTATION_SPEED * 0.06);
    data->ply->angle = normalize_angle(data->ply->angle);
    data->ply->look_offset -= mouse_delta_y * 2;
    return 0;
}

int mouse_release(int button, int x, int y, t_data *data)
{
    data->ply->turn_direction = 0;
    update_player(data->ply, data);
    return 0;
}
int key_release(int keycode, t_data *data)
{
    if (keycode == ON_KEYUP || keycode == ON_KEYDOWN || keycode == 102)
        data->ply->walk_direction = 0;
    if (keycode == ON_TURN_LEFT || keycode == ON_TURN_RIGHT)
        data->ply->turn_direction = 0;
    if (keycode == 102)
        data->ply->move_speed = 1;
    return 0;
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx->mlx, data->mlx->win);
    stop_all_sounds(data);
    exit(0);
    return 0;
} 
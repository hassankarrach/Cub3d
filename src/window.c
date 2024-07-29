#include "../includes/cub3d.h"


void handle_events(t_data *data)
{
    mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
    mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
    mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ON_KEYUP)
        data->ply->move_up = 1;
    if (keycode == ON_KEYDOWN)
        data->ply->move_down = 1;
    if (keycode == ON_MOVE_LEFT)
        data->ply->move_left = 1;
    if (keycode == ON_MOVE_RIGHT)
        data->ply->move_right = 1;
    if (keycode == ON_TURN_LEFT)
        data->ply->turn_left = 1;
    if (keycode == ON_TURN_RIGHT)
        data->ply->turn_right = 1;
    return 0;
}

int key_release(int keycode, t_data *data)
{
    if (keycode == ON_KEYUP)
        data->ply->move_up = 0;
    if (keycode == ON_KEYDOWN)
        data->ply->move_down = 0;
    if (keycode == ON_MOVE_LEFT)
        data->ply->move_left = 0;
    if (keycode == ON_MOVE_RIGHT)
        data->ply->move_right = 0;
    if (keycode == ON_TURN_LEFT)
        data->ply->turn_left = 0;
    if (keycode == ON_TURN_RIGHT)
        data->ply->turn_right = 0;
    return 0;
}

int close_window(t_data *data)
{
    (void)data;
    // Implement the logic to close the window
    return 0;
}
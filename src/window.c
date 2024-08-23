#include "../includes/cub3d.h"

void handle_events(t_data *data)
{
    mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
    mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
    mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
}

int key_press(int keycode, t_data *data)
{
    printf ("%d\n", keycode);
    if (keycode == ON_KEYUP)
        data->ply->walk_direction = -1;
    if (keycode == ON_KEYDOWN)
        data->ply->walk_direction = 1;
    if (keycode == ON_TURN_LEFT)
        data->ply->turn_direction = -1;
    if (keycode == ON_TURN_RIGHT)
        data->ply->turn_direction = 1;
    update_player(data->ply);
    return 0;
}

int key_release(int keycode, t_data *data)
{
    if (keycode == ON_KEYUP)
        data->ply->walk_direction = 0;
    if (keycode == ON_KEYDOWN)
        data->ply->walk_direction = 0;
    if (keycode == ON_TURN_LEFT)
        data->ply->turn_direction = 0;
    if (keycode == ON_TURN_RIGHT)
        data->ply->turn_direction = 0;
    return 0;
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx->mlx, data->mlx->win);
    exit(0);
    return 0;
}
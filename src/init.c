// Functions for initializing the game, loading resources, etc.
#include "../includes/cub3d.h"
void init_player(t_player *player, t_data *data) {
    get_x_y_player(data);
    player->fov_rd = 60 * DEG_TO_RAD;
    player->angle = 0;
    // player->dirX = -1;
    // player->dirY = 0;
    // player->planeX = 0;
    player->planeY = 0.66;
    player->move_up = 0;
    player->move_down = 0;
    player->move_left = 0;
    player->move_right = 0;
    player->turn_left = 0;
    player->turn_right = 0;
}
void init_ray(t_ray *ray) {
    ray->ray_ngl = 0;
    ray->distance = 0;
    ray->angleIncrement = 0;
}
void init_game(t_data *data, t_args *args)
{

    data->args = args;
    data->map2d = args->map_lines;
    data->ply = malloc(sizeof(t_player));
    init_player(data->ply, data);
    data->ray = malloc(sizeof(t_ray));
    init_ray(data->ray);
    data->mlx = malloc(sizeof(t_mlx));
    data->mlx->mlx = mlx_init();
    data->mlx->win = mlx_new_window(data->mlx->mlx, S_W, S_H, "Cub3D");
    data->mlx->img = mlx_new_image(data->mlx->mlx, S_W, S_H);
    data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
    // data->tex = malloc(sizeof(t_tex));
    // init_textures(data->tex);
}
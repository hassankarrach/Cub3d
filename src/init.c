// Functions for initializing the game, loading resources, etc.
#include "../includes/cub3d.h"
void init_player(t_player *player, t_data *data) {
    get_x_y_player(data);
    player->posX = data->index_x * 32 + 16;
    player->posY = data->index_y * 32 + 16;
    player->fov_rd = 60 * DEG_TO_RAD;
    player->walk_direction = 0;
    player->turn_direction = 0;
    get_angle(data);
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
    data->w_map = 20;
    data->h_map = 8;
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
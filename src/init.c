// Functions for initializing the game, loading resources, etc.
#include "../includes/cub3d.h"
void init_player(t_player *player, t_data *data)
{
    get_x_y_player(data);
    player->posX = data->index_x * TILE_SIZE + 288;
    player->posY = data->index_y * TILE_SIZE + 288;
    player->fov_rd = 60 * DEG_TO_RAD;
    player->walk_direction = 0;
    player->turn_direction = 0;
    data->ply->move_speed = 1;
    data->ply->bobbing_speed = 1;
    data->ply->bobbing_amplitude = 1;
    get_angle(data);
}
void init_ray(t_ray *ray)
{
    ray->ray_ngl = 0;
    ray->angleIncrement = 0;
}
static void init_sounds(t_data *data)
{
    int i = 0;
    data->sounds[0].file_path = LOBBY_SOUND_PATH;
    data->sounds[1].file_path = AMBIENCE_SOUND_PATH;
    data->sounds[2].file_path = PSST_SOUND_PATH;
    data->sounds[3].file_path = WALKING_SOUND_PATH;
    data->sounds[4].file_path = YOU_DEAD_SOUND_PATH;

    while (i < 5)
        data->sounds[i++].is_playing = 0;
    i = 0;
    while (i < 5)
        data->sounds[i++].pid = 0; // should be?
}
void init_game(t_data *data, t_args *args)
{

    data->args = args;
    data->map2d = args->map_lines;
    data->w_map = 37;
    data->h_map = 16;
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
    data->state = LOBBY;
    init_sounds(data);
}
#include "../../includes/cub3d.h"

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
    data->door->is_open = 0;
    get_angle(data);
}
void init_ray(t_ray *ray)
{
    ray->ray_ngl = 0;
    // ray->angleIncrement = 0;
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
void load_door_textures(t_data *data)
{
    data->textures.door[0] = texture_loader(data, "./assets/textures/door1.xpm");
    data->textures.door[1] = texture_loader(data, "./assets/textures/door2.xpm");
    data->textures.door[2] = texture_loader(data, "./assets/textures/door3.xpm");
    data->textures.door[3] = texture_loader(data, "./assets/textures/door4.xpm");
    data->textures.door[4] = texture_loader(data, "./assets/textures/door5.xpm");
    data->textures.door[5] = texture_loader(data, "./assets/textures/door6.xpm");
    data->textures.door[6] = texture_loader(data, "./assets/textures/door7.xpm");
    data->textures.door[7] = texture_loader(data, "./assets/textures/door8.xpm");
}
void load_wall_textures(t_data *data)
{
    data->textures.wall_EA = texture_loader(data, data->args->East_texture);
    data->textures.wall_NO = texture_loader(data, data->args->North_texture);
    data->textures.wall_SO = texture_loader(data, data->args->South_texture);
    data->textures.wall_WE = texture_loader(data, data->args->West_texture);
}

void load_all_textures(t_data *data)
{
    // Frames
    data->textures.wall_frame1 = texture_loader(data, "./assets/textures/wall_with_frame.xpm");
    data->textures.wall_frame2 = texture_loader(data, "./assets/textures/wall_with_frame2.xpm");
    // Assets
    data->textures.mini_map = texture_loader(data, "./assets/mini_map.xpm");
    data->textures.icon_player = texture_loader(data, "./assets/player_icon.xpm");
    data->textures.logo = texture_loader(data, "./assets/logo.xpm");
    data->textures.press_to_start = texture_loader(data, "./assets/press_space.xpm");
    data->textures.you_died = texture_loader(data, "./assets/you_died.xpm");

    load_wall_textures(data);
    load_door_textures(data);
}
void init_doors(t_data *data, t_door *door, t_texture **door_textures)
{
    door->is_open = 0;
    door->distance = sqrt(pow(data->w_map * TILE_SIZE, 2) + pow(data->h_map * TILE_SIZE, 2));
    door->current_frame = 0;
    door->total_frames = 8; // Assume 8 frames for the door animation
    door->last_update_time = 0;
    for (int k = 0; k < door->total_frames; k++)
    {
        door->textures[k] = door_textures[k];
    }
}
void init_game(t_data *data, t_args *args)
{

    data->args = args;
    data->map2d = args->map_lines;
    data->w_map = 37;
    data->h_map = 16;
    data->door = malloc(sizeof(t_door));
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
    load_door_textures(data);
    init_doors(data, data->door, data->textures.door);
    load_all_textures(data);
}
#include "../../includes/renderer.h"
// t_door *get_corret_door(t_door **list_door, x, y)
// {
//     int i;
//     int j;

//     i = (int)(x / (double)TILE_SIZE);
//     j = (int)(y / (double)TILE_SIZE);
//     while (list_door && list_door->next != NULL)
//     {
//         if (list_door->x == i && list_door->y == j)
//             break;
//     }
//     return (*list_door);
// }
void update_door_animation(t_data *data, t_door *door, double current_time)
{
    double time_between_frames = 0.1; // 100 ms between frames
    t_door *corret_door;

    // corret_door = get_corret_door(door, door->x_intercept, door->y_intercept)
    if (current_time - door->last_update_time >= time_between_frames)
    {
        if (door->is_open && door->current_frame < door->total_frames - 1)
            door->current_frame++;
        else if (!door->is_open && door->current_frame)
            door->current_frame--;
        door->last_update_time = current_time;
    }
}

int get_start_drawing_texture_x_door(t_door door_ray)
{
    int offset;
    
    if (door_ray.is_ver_ray == 1) // Horizontal hit
    {
        offset = (int)door_ray.x_intercept % TILE_SIZE;
    }
    else // Vertical hit
    {
        offset = (int)door_ray.y_intercept % TILE_SIZE;
    }
    return offset;
}

t_texture *selected_texture_door(t_data *data, t_ray ray)
{
    return (data->textures.door[data->door->current_frame]);
}

double get_door_height(t_door *door, t_ray *ray, t_player ply)
{
    double dis_player;
    double wall_height;
    double distance;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);   // Distance from player to projection plane 
    distance = door->distance * cos(ply.angle - ray->ray_ngl);
    wall_height = (dis_player * TILE_SIZE) / distance;
    return wall_height;
}
t_wall_params calculate_door_params(t_data *data)
{
    t_wall_params params;

    params.wall_height = get_door_height(data->door, data->ray, *data->ply);
    params.start_y = (S_H / 2) - ((int)params.wall_height / 2) + data->ply->look_offset;
    params.end_y = (S_H / 2) + ((int)params.wall_height / 2) + data->ply->look_offset;
    params.save_y = params.start_y;
    if (params.start_y < 0)
        params.start_y = 0;
    if (params.end_y >= S_H)
        params.end_y = S_H - 1;
    if (params.end_y >= S_H)
        params.end_y = S_H - 1;
    return params;
}
int apply_brightness(int color, double brightness_factor)
{
    int r;
    int g;
    int b;
    
    r = ((color >> 16) & 0xFF) * brightness_factor;
    r = clamp(r, 0, 255);
    g = ((color >> 8) & 0xFF) * brightness_factor;
    g = clamp(g, 0, 255);
    b = (color & 0xFF) * brightness_factor;
    b = clamp(b, 0, 255);
    return (r << 16) | (g << 8) | b;
}

void rendring_door(t_data *data, t_door door, int x)
{
    int texture_x, texture_y;
    t_wall_params wall_params;
    double brightness_factor;

    wall_params = calculate_door_params(data);
    texture_x = get_start_drawing_texture_x_door(*data->door);
    brightness_factor = 1.0 - (door.distance / (TILE_SIZE * 12));
    t_texture *texture = selected_texture_door(data, *data->ray);
    while (wall_params.start_y <= wall_params.end_y)
    {
        texture_y = ((wall_params.start_y - wall_params.save_y) * 576) / wall_params.wall_height;
        int color = get_pixel_from_texture(texture, texture_x, texture_y);
        if (color == 0)
        {
            wall_params.start_y++;
            continue;   
        }
        color = apply_brightness(color, brightness_factor);
        ft_pixel_put(data, x, wall_params.start_y, color);
        wall_params.start_y++;
    }
}
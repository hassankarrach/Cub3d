#include "../includes/cub3d.h"
void Head_Bobbing(t_data *data)
{
    static double bobbing_time = 0;
    
    if (data->ply->walk_direction)
    {
        bobbing_time += BOBBING_SPEED * data->ply->move_speed;
        data->ply->look_offset += sin(bobbing_time) * BOBBING_AMPLITUDE * data->ply->move_speed; // sin(bobbing_time) gives a value between -1 and 1
    }
    else
    {
        bobbing_time = 0;
    }
}
void update_player(t_player *player, t_data *data)
{
    double new_x;
    double new_y;

    new_x = player->posX;
    new_y = player->posY;
    player->angle += player->turn_direction * ROTATION_SPEED;
    player->angle = normalize_angle(player->angle);
    new_x += player->walk_direction * MOVE_SPEED * data->ply->move_speed * cos(player->angle);
    new_y += player->walk_direction * MOVE_SPEED * data->ply->move_speed * sin(player->angle);
    if (!find_wall(data, new_x, player->posY))  // Check X-axis
        player->posX = new_x;
    if (!find_wall(data, player->posX, new_y))  // Check Y-axis
        player->posY = new_y;
    Head_Bobbing(data);
}
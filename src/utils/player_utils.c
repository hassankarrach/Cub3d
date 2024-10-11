#include "../../includes/utils.h"

static int valid_move(t_data *data, double x, double y)
{
    int i = (int)(x / TILE_SIZE);
    int j = (int)(y / TILE_SIZE);
    double start_door;
    double end_door;

    start_door = 200.0;
    end_door = 376.0;
    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    if (data->map2d[j][i] == '1')
        return 1;
    if (data->map2d[j][i] == 'D' || data->map2d[j][i] == 'O')
    {
        if ((fmod(x, TILE_SIZE) >= start_door && fmod(x, TILE_SIZE) <= end_door))
            return 0;
        else
            return (1);
    }
    return 0;
}
void Head_Bobbing(t_data *data)
{
    static double bobbing_time = 0;
    
    if (data->ply->walk_direction)
    {
        bobbing_time += BOBBING_SPEED * data->ply->bobbing_speed; 
        data->ply->look_offset += sin(bobbing_time) * BOBBING_AMPLITUDE * data->ply->bobbing_amplitude; // sin(bobbing_time) gives a value between -1 and 1
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
    if (!valid_move(data, new_x, player->posY))  // Check X-axis
    {
        player->posX = new_x;
        data->index_x = new_x / TILE_SIZE;
    }
    if (!valid_move(data, player->posX, new_y))  // Check Y-axis
    {
        player->posY = new_y;
        data->index_y = new_y / TILE_SIZE;
    }
    Head_Bobbing(data);
}
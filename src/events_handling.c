#include "../includes/cub3d.h"
void update_player(t_player *player, t_data *data)
{
    double new_x;
    double new_y;

    new_x = player->posX;
    new_y = player->posY;
    player->angle += player->turn_direction * ROTATION_SPEED;
    player->angle = normalize_angle(player->angle);
    new_x += player->walk_direction * MOVE_SPEED * cos(player->angle);
    new_y += player->walk_direction * MOVE_SPEED * sin(player->angle);
    if (!find_wall(data, new_x, new_y))
    {
        player->posX = new_x;
        player->posY = new_y;
    }
}
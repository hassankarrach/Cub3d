#include "../../includes/utils.h"

static bool hit_wall(t_data *data, double x, double y)
{
    int i;
    int j;
        double start_door;
    double end_door;

    start_door = 220.0;
    end_door = 380.0;
    i = (int)(x / (double)TILE_SIZE);
    j = (int)(y / (double)TILE_SIZE);
    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    if (data->map2d[j][i] == '1' || data->map2d[j][i] == 'F')
        return 1;
    else if (data->map2d[j][i] == 'D' || data->map2d[j][i] == 'O')
        if (!(fmod(x, TILE_SIZE) >= start_door && fmod(x, TILE_SIZE) <= end_door) && ft_distance(data, data->door->x_intercept, data->door->y_intercept) < 60.0 && data->ply->walk_direction >= 0)
            return 1;
    return (0);
}
static int valid_move2(t_data *data, double x, double y)
{
    if (hit_wall(data, x + 25, y - 25))
        return 1;
    else if (hit_wall(data, x - 25 , y + 25))
        return 1;
    else if (hit_wall(data, x - 25 , y - 25))
        return 1;
    else if (hit_wall(data, x + 25, y + 25))
        return 1;
    return (0);
}
static int valid_move(t_data *data, double x, double y)
{
    int i;
    int j;
    i = (int)(x / (double)TILE_SIZE);
    j = (int)(y / (double)TILE_SIZE);
    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    else if (valid_move2(data, x, y))
        return (1);
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
    new_x += player->walk_direction * (MOVE_SPEED * data->ply->move_speed) * cos(player->angle);
    new_y += player->walk_direction * (MOVE_SPEED * data->ply->move_speed) * sin(player->angle);
    if (!valid_move(data, new_x, player->posY))  // Check X-axis
    {
        player->posX = new_x;
    }
    if (!valid_move(data, player->posX, new_y))  // Check Y-axis
    {
        player->posY = new_y;
    }
    Head_Bobbing(data);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
    if (x >= 0 && x < S_W && y >= 0 && y < S_H)
	    *(int *)dst = color;
}
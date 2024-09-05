#include "../includes/cub3d.h"
double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}
float calculate_distance(t_data *data, float angle)
{
    float smallest_distance;
    float h_distance;
    float v_distance;

    h_distance = get_h_inter(data, angle);
    v_distance = get_v_inter(data, angle);
    if (h_distance <= v_distance)
        smallest_distance = h_distance;
    else
        smallest_distance = v_distance;
    return (smallest_distance);
}
void start_h_y(t_data *data, float angl, float *h_y)
{
    if (isRayFacingDown(angl))
    {  // Ray facing downwards
        *h_y = floor(data->ply->posY / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    }
    else    
    {  // Ray facing upwards
        *h_y = floor(data->ply->posY / TILE_SIZE) * TILE_SIZE;
    }
}
void start_v_x(t_data *data, float angl, float *v_x)
{
    if (isRayFacingLeft(angl))
    {  // Ray facing left
        *v_x = floor(data->ply->posX / TILE_SIZE) * TILE_SIZE;
    }
    else
    {  // Ray facing right
        *v_x = floor(data->ply->posX / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    }
}
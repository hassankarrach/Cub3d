#include "../../includes/raycaster.h"

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}
double ft_distance(t_data *data, double x, double y)
{
    double dx;
    double dy;

    dx = x - data->ply->posX;
    dy = y - data->ply->posY;
    return sqrt((dx * dx) + (dy * dy));
}
static t_inter min_distance(t_inter inter_h, t_inter inter_v, t_data *data)
{
    double h_dist = ft_distance(data, inter_h.xintercept, inter_h.yintercept);
    double v_dist = ft_distance(data, inter_v.xintercept, inter_v.yintercept);

    if (h_dist <= v_dist)
    {
        data->ray->v_or_h = 1;   // Horizontal hit
        return inter_h;
    }
    else
    {
        data->ray->v_or_h = 0;   // Vertical hit
        return inter_v;
    }
}
double calculate_distance(t_data *data, float angle)
{
    t_inter result_inter;
    t_inter inter_h;
    t_inter inter_v;

    inter_h = get_h_inter(data, angle);
    inter_v = get_v_inter(data, angle);
    result_inter = min_distance(inter_h, inter_v, data);
    data->ray->min_inter.xintercept = result_inter.xintercept;
    data->ray->min_inter.yintercept = result_inter.yintercept;
    return ft_distance(data, result_inter.xintercept, result_inter.yintercept);
}
void start_h_y(t_data *data, double angl, double *h_y)
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
void start_v_x(t_data *data, double angl, double *v_x)
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
void start_h_y_door(t_data *data, double angl, double *h_y)
{
    double tile_size;

    tile_size = TILE_SIZE / 2;
    if (isRayFacingDown(angl))
    {  // Ray facing downwards
        *h_y = floor(data->ply->posY / tile_size) * tile_size + tile_size;
    }
    else    
    {  // Ray facing upwards
        *h_y = floor(data->ply->posY / tile_size) * tile_size;
    }

    // Center the door in the tile by adjusting h_y to the middle
    // *h_y = *h_y - TILE_SIZE / 2;
}
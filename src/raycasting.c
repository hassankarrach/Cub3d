// Functions implementing the raycasting algorithm
// ray casting algrihtm
// 1. find cooordinate of the first intersection point
// 2. find y and x step (the distance between the intersection points)
// 3. convert intersection point (x, y) into map index [i][j]
// if intersection hits a wall, stop the loop
// else find the next intersection point
// 4. calculate the distance between the player and the intersection point

#include "../includes/cub3d.h"
int find_wall(t_data *data, double x, double y)
{
    int i = (int)floor(x / TILE_SIZE);
    int j = (int)floor(y / TILE_SIZE);

    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    if (data->map2d[j][i] == '1')
        return 1;
    if (data->map2d[j][i] == 'D' || (data->map2d[j][i] == 'O'))
    {
        if (data->ray->skip_door)
            return (0);
        else
            return 1;
    }
    return 0;
}
bool is_door(double x, double y, t_data *data)
{
    int i;
    int j;
    float dist_door;

    i = (int)floor(x / TILE_SIZE);
    j = (int)floor(y / TILE_SIZE);
    dist_door = ft_distance(data, x, y);
    if (i < 0 || i >= data->w_map || j < 0 || j >= data->h_map)
        return false;
    if (data->map2d[j][i] == 'D')
    {
        if (dist_door < 600.0 && !data->door->is_open)
        {
            data->door->is_open = 1;
            data->map2d[j][i] = 'O';
        }
        return true;
    }
    else if (data->map2d[j][i] == 'O')
    {
        if (dist_door > 600.0)
        {
            data->door->is_open = 0;
            data->map2d[j][i] = 'D';
        }
        return true;
    }
    return false;
}
bool player_in_grid(t_data *data)
{
    int player_tile_x;  
    int player_tile_y;

    player_tile_x = (int)(data->ply->posX / TILE_SIZE);
    player_tile_y = (int)(data->ply->posY / TILE_SIZE);
    if (data->map2d[player_tile_y][player_tile_x] == 'D' || data->map2d[player_tile_y][player_tile_x] == 'O')
        return true;
    else
        return (false);
}

bool check_door_in_grid(t_data *data, t_inter *inter_h, double x_step, double y_step)
{
    double save_inter_x;
    double save_inter_y;

    save_inter_x = inter_h->xintercept;
    save_inter_y =inter_h->yintercept;
    if (player_in_grid(data))
    {
        start_h_y_door(data, data->ray->ray_ngl, &inter_h->yintercept);
        inter_h->xintercept = data->ply->posX + (inter_h->yintercept - data->ply->posY) / tan(data->ray->ray_ngl);
        if (fmod(data->ply->posY, TILE_SIZE) < TILE_SIZE / 2 && isRayFacingUp(data->ray->ray_ngl))
        {
            inter_h->xintercept = save_inter_x;
            inter_h->yintercept = save_inter_y;
            return false;
        }
        return (true);
    }
    inter_h->xintercept += x_step / 2;
    inter_h->yintercept += y_step / 2;
    return false;
}

t_inter get_h_inter(t_data *data, float angl)
{
    t_inter inter_h;
    double x_step;
    double y_step;

    inter_h.is_door = false;
    y_step = TILE_SIZE;
    start_h_y(data, angl, &inter_h.yintercept);
    inter_h.xintercept = data->ply->posX + (inter_h.yintercept - data->ply->posY) / tan(angl);
    if (isRayFacingUp(angl))
        y_step *= -1;
    x_step = y_step / tan(angl);
    if (isRayFacingLeft(angl) && x_step > 0 || isRayFacingRight(angl) && x_step < 0)
        x_step *= -1;
    if (isRayFacingUp(angl))
        inter_h.yintercept -= 0.0001;
    while (!find_wall(data, inter_h.xintercept, inter_h.yintercept))
    {
        inter_h.yintercept += y_step;
        inter_h.xintercept += x_step;
    }
    if (!data->ray->skip_door && check_door_in_grid(data, &inter_h, x_step, y_step))
            return (inter_h);
    return (inter_h);
}

t_inter get_v_inter(t_data *data, float angl)
{
    t_inter inter_v;
    double x_step;
    double y_step;

    inter_v.is_door = false;
    x_step = TILE_SIZE;
    start_v_x(data, angl, &inter_v.xintercept);
    inter_v.yintercept = data->ply->posY + (inter_v.xintercept - data->ply->posX) * tan(angl);
    if (isRayFacingLeft(angl))
        x_step *= -1;
    y_step = x_step * tan(angl);
    if (isRayFacingUp(angl) && y_step > 0 || (isRayFacingDown(angl) && y_step < 0))
        y_step *= -1;
    if (isRayFacingLeft(angl))
        inter_v.xintercept -= 0.0001;
    while (!find_wall(data, inter_v.xintercept, inter_v.yintercept))
    {
        inter_v.xintercept += x_step;
        inter_v.yintercept += y_step;
    }
    return (inter_v);
}
void cast_rays_door(t_data *data, int ray)
{
    data->ray->skip_door = 0;
    data->door->distance = calculate_distance(data, data->ray->ray_ngl);
    data->door->x_intercept = data->ray->min_inter.xintercept;
    data->door->y_intercept = data->ray->min_inter.yintercept;
    data->door->is_ver_ray = data->ray->v_or_h;
    if (is_door(data->door->x_intercept, data->door->y_intercept, data) &&  data->ray->v_or_h == 1)
        rendring_door(data, *data->door, ray);
}
void raycasting(t_data *data)
{
    double angle;
    int ray;
    double angleIncrement;

    ray = 0;
    data->ray->ray_ngl = data->ply->angle - data->ply->fov_rd / 2;
    angleIncrement = data->ply->fov_rd / S_W;
    while (ray < S_W)
    {
        data->ray->skip_door = 1;
        data->ray->ray_ngl = normalize_angle(data->ray->ray_ngl);
        data->ray->distance = calculate_distance(data, data->ray->ray_ngl);
        render_wall(data, ray);
        cast_rays_door(data, ray);
        ray++;
        data->ray->ray_ngl += angleIncrement; // next angle
    }
}
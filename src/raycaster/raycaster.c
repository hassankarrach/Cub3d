#include "../../includes/raycaster.h"

int find_wall(t_data *data, double x, double y)
{
    int i = (int)floor(x / TILE_SIZE);
    int j = (int)floor(y / TILE_SIZE);

    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    if (data->map2d[j][i] == '1' || data->map2d[j][i] == 'F')
        return 1;
    if (data->map2d[j][i] == 'D' || (data->map2d[j][i] == 'O'))
    {
        data->ray->hit_door = 1;
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

    player_tile_x = (int)floor(data->ply->posX / TILE_SIZE);
    player_tile_y = (int)floor(data->ply->posY / TILE_SIZE);
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
    save_inter_y = inter_h->yintercept;
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
    t_door *door;

    door = data->door;
    data->ray->skip_door = 0;
    door->distance = calculate_distance(data, data->ray->ray_ngl);
    door->x_intercept = data->ray->min_inter.xintercept;
    door->y_intercept = data->ray->min_inter.yintercept;
    door->is_ver_ray = data->ray->v_or_h;
    if (is_door(door->x_intercept, door->y_intercept, data) &&  data->ray->v_or_h == 1)
        rendring_door(data, *data->door, ray);
    data->ray->hit_door = false;
}
void raycasting(t_data *data)
{
    t_ray *ray;
    double angle;
    int ray_x;
    double angleIncrement;

    ray_x = 0;
    ray = data->ray;
    angle = data->ply->angle - data->ply->fov_rd / 2;
    angleIncrement = data->ply->fov_rd / S_W;
    while (ray_x < S_W)
    {
        data->ray->skip_door = 1;
        angle = normalize_angle(angle);
        ray->ray_ngl = angle;
        ray->distance = calculate_distance(data, angle);
        render_wall(data, ray_x, ray->ray_ngl);
        if (data->ray->hit_door || player_in_grid(data))
            cast_rays_door(data, ray_x);
        ray_x++;
        angle += angleIncrement; // next angle
    }
}
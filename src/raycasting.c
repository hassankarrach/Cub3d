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
    int i = floor(x / TILE_SIZE);
    int j = floor(y / TILE_SIZE);

    // Correct distance from door (use center of tile)
    float door_x_center = (i * TILE_SIZE) + TILE_SIZE / 2;
    float door_y_center = (j * TILE_SIZE) + TILE_SIZE / 2;
    float dist_door = sqrt(pow(door_x_center - data->ply->posX, 2) + pow(door_y_center - data->ply->posY, 2));

    if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
        return 1;
    if (data->map2d[j][i] == '1')
        return 1;
    if (data->map2d[j][i] == 'D')
    {
        if (dist_door < 1000.0)
        {
            data->map2d[j][i] = 'O';
        }
        data->ray->hit_door = 1;
        return 1;
    }
    if (data->map2d[j][i] == 'O')
    {
        if (dist_door > 1000.0)
        {
            data->map2d[j][i] = 'D';
        }
        data->ray->hit_door = 0;
        return 0;
    }
    return 0;
}

float get_h_inter(t_data *data, float angl)
{
    float x_step;
    float y_step;
    float xintercept_h;
    float yintercept_h;

    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(angl);
    start_h_y(data, angl, &yintercept_h);
    xintercept_h = data->ply->posX + (yintercept_h - data->ply->posY) / tan(angl);
    if (isRayFacingUp(angl))
        y_step *= -1;
    if (isRayFacingLeft(angl) && x_step > 0 || isRayFacingRight(angl) && x_step < 0)
        x_step *= -1;
    while (!find_wall(data, xintercept_h, yintercept_h - (float)isRayFacingUp(angl)))
    {
        yintercept_h += y_step;
        xintercept_h += x_step;
    }
    return (sqrt(pow(xintercept_h - data->ply->posX, 2) + pow(yintercept_h - data->ply->posY, 2)));
}
float get_v_inter(t_data *data, float angl)
{
    float x_step;
    float y_step;
    float xintercept_h;
    float yintercept_h;

    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angl);
    start_v_x(data, angl, &xintercept_h);
    yintercept_h = data->ply->posY + (xintercept_h - data->ply->posX) * tan(angl);
    if (isRayFacingLeft(angl))
        x_step *= -1;
    if (isRayFacingUp(angl) && y_step > 0 || (isRayFacingDown(angl) && y_step < 0))
        y_step *= -1;
    while (!find_wall(data, xintercept_h - (float)isRayFacingLeft(angl), yintercept_h))
    {
        xintercept_h += x_step;
        yintercept_h += y_step;
    }
    return (sqrt(pow(xintercept_h - data->ply->posX, 2) + pow(yintercept_h - data->ply->posY, 2)));
}
void set_inter_point(t_data *data)
{
    data->ray->h_x = data->ply->posX + data->ray->h_distance * cos(data->ray->ray_ngl);
    data->ray->v_y = data->ply->posY + data->ray->v_distance * sin(data->ray->ray_ngl);
}
void raycasting(t_data *data)
{
    double angle;
    int ray;

    ray = 0;
    data->ray->ray_ngl = data->ply->angle - data->ply->fov_rd / 2;
    data->ray->angleIncrement = data->ply->fov_rd / S_W;
    draw_sky_floor(data);
    floor_casting(data, ray);
    while (ray < S_W)
    {
        data->ray->hit_door = 0;
        data->ray->ray_ngl = normalize_angle(data->ray->ray_ngl);
        data->ray->distance = calculate_distance(data, data->ray->ray_ngl);
        // set_floor_coords(data, ray);
        set_inter_point(data);
        // render_mini_map(data, data->args->map_lines);
        render_wall(data, data->ray->distance, ray, data->ray->ray_ngl);
        // draw_2d_game(data);
        // int endX = data->ply->posX + cos(data->ray->ray_ngl) * data->ray->distance;
        // int endY = data->ply->posY + sin(data->ray->ray_ngl) * data->ray->distance;
        // draw_line(data, data->ply->posX, data->ply->posY, endX, endY);
        ray++;
        data->ray->ray_ngl += data->ray->angleIncrement; // next angle
    }
}

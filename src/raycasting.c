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
    int i;
    int j;

    if (x < 0 || y < 0)
        return (1);
    i = floor(x / TILE_SIZE);
    j = floor(y / TILE_SIZE);
    // printf("i = %d j = %d\n", i, j);
    // printf ("%d\n", data->h_map);
    if (i >= data->w_map || j >= data->h_map)
        return 1;
    if (data->args->map_lines[j][i] == '1')
        return 1;
    return 0;
}
float get_h_inter(t_data *data, float angl)
{
    float x_step;
    float y_step;
    float xintercept;
    float yintercept;

    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(angl);
    start_h_y(data, angl, &yintercept);
    xintercept = data->ply->posX + (yintercept - data->ply->posY) / tan(angl);
    if (isRayFacingUp(angl))
        y_step *= -1;
    if (isRayFacingLeft(angl) && x_step > 0 || isRayFacingRight(angl) && x_step < 0)
        x_step *= -1;
    while (!find_wall(data, xintercept, yintercept - (float)isRayFacingUp(angl)))
    {
        yintercept += y_step;
        xintercept += x_step;
    }
    return (sqrt(pow(xintercept - data->ply->posX, 2) + pow(yintercept - data->ply->posY, 2)));
}
float get_v_inter(t_data *data, float angl)
{
    float x_step;
    float y_step;
    float xintercept;
    float yintercept;

    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angl);
    start_v_x(data, angl, &xintercept);
    yintercept = data->ply->posY + (xintercept - data->ply->posX) * tan(angl);
    if (isRayFacingLeft(angl))
        x_step *= -1;
    if (isRayFacingUp(angl) && y_step > 0 || (isRayFacingDown(angl) && y_step < 0))
        y_step *= -1;
    while (!find_wall(data, xintercept - (float)isRayFacingLeft(angl), yintercept))
    {
        xintercept += x_step;
        yintercept += y_step;
    }
    return (sqrt(pow(xintercept - data->ply->posX, 2) + pow(yintercept - data->ply->posY, 2)));
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
    while (ray < S_W)
    {
        data->ray->ray_ngl = normalize_angle(data->ray->ray_ngl);
        data->ray->distance = calculate_distance(data, data->ray->ray_ngl);
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
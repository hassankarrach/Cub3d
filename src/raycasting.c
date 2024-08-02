// Functions implementing the raycasting algorithm 
// ray casting algrihtm
// 1. find cooordinate of the first intersection point
// 2. find y and x step (the distance between the intersection points)
// 3. convert intersection point (x, y) into map index [i][j]
// if intersection hits a wall, stop the loop
// else find the next intersection point
// 4. calculate the distance between the player and the intersection point

#include "../includes/cub3d.h"
int find_wall(t_data *data, float x, float y) // find the wall
{
    int i;  
    int j;

    i = floor(y / TILE_SIZE);
    j = floor(x / TILE_SIZE);
    if (i < 0 || i >= data->h_map || j < 0 || j >= data->w_map) // if the index is out of bounds
        return (1);
    if (data->args->map_lines[i][j] == '1')
        return (1);
    return (0);
}
float get_h_inter(t_data *data, float angl) // get the horizontal intersection
{
    float x_step;
    float y_step;
    int hit;
    float xintercept;
    float yintercept;

    hit = 0;
    y_step = TILE_SIZE; // get the y step
    x_step = TILE_SIZE / tan(angl);  // get the x step
    start_h_y(data, angl, &yintercept);
    xintercept = data->ply->posX + (yintercept - data->ply->posY) / tan(angl); // get the x coordinate
    if (angl > 0 && angl < M_PI) // Ray facing downwards
        y_step *= -1;
    if (((angl > M_PI / 2 && angl < 3 * M_PI / 2) && x_step > 0) || ((angl >  0 && angl < M_PI) && x_step < 0)) // Ray facing left or right (x_step should be negative)
        x_step *= -1;
    while (hit == 0)
    {
        if (find_wall(data, xintercept, yintercept) == 1)
            hit = 1;
        else
        {
            yintercept += y_step; // move to the next y coordinat 
            xintercept += x_step; // move to the next x coordinate
        }
    }
    return (sqrt(pow(xintercept - data->ply->posX, 2) + pow(yintercept - data->ply->posY, 2))); // get the distance
}
float get_v_inter(t_data *data, float angl) // get the vertical intersection
{
    float x_step;
	float y_step;
    int hit;
    float xintercept;
    float yintercept;

    hit = 0;
    x_step = TILE_SIZE; // get the x step
    y_step = TILE_SIZE * tan(angl); // get the y step
    start_v_x(data, angl, &xintercept);
    yintercept = data->ply->posY + (xintercept - data->ply->posX) * tan(angl); // get the y coordinate
    if (angl > M_PI / 2 && angl < 3 * M_PI / 2) // Ray facing left
        x_step *= -1;
    if (((angl > 0 && angl < M_PI) && y_step > 0) || ((angl > M_PI && angl < 2 * M_PI) && y_step < 0)) // Ray facing up or down (y_step should be negative)
        y_step *= -1;
    while (hit == 0)
    {
        if (find_wall(data, xintercept, yintercept) == 1)
            hit = 1;
        else
        {
            xintercept += x_step;  // move to the next x coordinate
            yintercept += y_step;  // move to the next y coordinate
        }
    }
    return (sqrt(pow(xintercept - data->ply->posX, 2) + pow(yintercept - data->ply->posY, 2))); // get the distance
}
void raycasting(t_data *data)
{
    double angle;
    int ray;

    ray = 0;
    data->ray->ray_ngl = data->ray->ray_ngl - data->ply->fov_rd / 2; // get the start angle
    data->ray->angleIncrement = data->ply->fov_rd / S_W; // get the angle increment
    while (ray < S_W) 
    {
        angle = normalize_angle(data->ray->ray_ngl); // normalize (should be between 0 and 2 * PI) the angle between 0 and 2 * PI becuase the angle is in radians
        data->ray->distance = calculate_distance(data, angle); // get the distance to the intersection point
        // render_mini_map(data, data->args->map_lines);
        // render_wall(data);
        ray++;
        data->ray->ray_ngl += data->ray->angleIncrement;  // next angle
    }

}
// Functions implementing the raycasting algorithm 

double normalize_angle(double angle) // normalize the angle
{
    while (angle < 0) angle += 2 * M_PI; // if the angle is less than 0 add 2 * PI
    while (angle >= 2 * M_PI) angle -= 2 * M_PI; // if the angle is greater than 2 * PI subtract 2 * PI
    return angle; // return the normalized angle
}
int inter_check(int angl, float *x, float *step, int is_horizontal) // check if there is a wall
{
    if (is_horizontal)
    {
        if (angl > M_PI && angl < 2 * M_PI)
        {
            *x = *x - 1;
            *step = -(*step);
        }
        else
        {
            *x = *x + TILE_SIZE;
        }
    }
    else
    {
        if (angl > M_PI / 2 && angl < 3 * M_PI / 2)
        {
            *x = *x - 1;
            *step = -(*step);
        }
        else
        {
            *x = *x + TILE_SIZE;
        }
    }
    if (data->map2d[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == 1)
        return 1;
    return 0;
}
float get_h_inter(t_data *data, float angl) // get the horizontal intersection
{
    float x_step;
    float y_step;

    y_step = TILE_SIZE; // get the y step
    x_step = TILE_SIZE / tan(angl);  // get the x step
    h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE; // get the y coordinate
    // pixel = inter_check(angl, &h_y, &y_step, 1); // check if there is a wall
    h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl); // get the x coordinate
    while (pixel == 0)
    {
        if (data->map2d[(int)(h_y / TILE_SIZE)][(int)(h_x / TILE_SIZE)] == 1)
            pixel = 1;
        else
        {
            h_y += y_step; // move to the next y coordinate
            h_x += x_step; // move to the next x coordinate
        }
    }
    return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + pow(h_y - mlx->ply->plyr_y, 2))); // get the distance
}
float get_v_inter(t_data *data, float angl) // get the vertical intersection
{
    float x_step;
	float y_step;
    int pixel;

    x_step = TILE_SIZE; // get the x step
    y_step = TILE_SIZE * tan(angl); // get the y step
    v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE; // get the x coordinate
    // pixel = inter_check(angl, &v_x, &x_step, 0); // check if there is a wall
    pixel = inter_check(angl, &v_x, &x_step, 0); // check if there is a wall
    v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl); // get the y coordinate
    while (pixel == 0)
    {
        if (data->map2d[(int)(v_y / TILE_SIZE)][(int)(v_x / TILE_SIZE)] == 1)
            pixel = 1;
        else
        {
            v_x += x_step;  // move to the next x coordinate
            v_y += y_step;  // move to the next y coordinate
        }
    }
    return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + pow(v_y - mlx->ply->plyr_y, 2))); // get the distance
}
void raycasting(t_data *data)
{
    double h_inter;
    double v_inter;
    double angle;
    int ray;

    ray = 0;
    data->ray->ray_ngl = data->ray->ray_ngl - data->player->fov_rd / 2; // get the start angle
    data->player->fov_rd = data->player->fov * DEG_TO_RAD; // convert the fov to radians
    data->ray->angleIncrement = data->player->fov_rd / S_W; // get the angle increment
    while (ray < S_W) 
    {
        angle = normalize_angle(data->ray->ray_ngl); // normalize (should be between 0 and 2 * PI) the angle between 0 and 2 * PI becuase the angle is in radians
        h_inter = get_h_inter(data, angle);
        v_inter = get_v_inter(data, angle);
        if (v_inter <= h_inter)
            data->ray->distance = v_inter;
        else
        {
            data->ray->distance = h_inter;
        }
        render(data, ray);
        ray++;
        data->ray->ray_ngl += data->ray->angleIncrement;  // next angle
    }
    
}
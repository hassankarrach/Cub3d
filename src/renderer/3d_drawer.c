#include "../../includes/renderer.h"

void draw_sky_floor(t_data *data)
{
    int x, y;
    int center_x = S_W / 2;
    int center_y_sky = (S_H / 2) + data->ply->look_offset;
    int max_distance_squared = (S_W / 2) * (S_W / 2) + S_H * S_H;
    double inv_max_distance = 1.0 / sqrt(max_distance_squared);

    int r_ceiling = data->args->Ceiling_color.r;
    int g_ceiling = data->args->Ceiling_color.g;
    int b_ceiling = data->args->Ceiling_color.b;

    #define LUT_SIZE 1024
    double pow_lut[LUT_SIZE];
    for (int i = 0; i < LUT_SIZE; i++) {
        double x = (double)i / (LUT_SIZE - 1);
        pow_lut[i] = x * x * x;
    }

    for (y = 0; y < S_H / 2 + data->ply->look_offset; y++)
    {
        int dy = y - center_y_sky;
        dy *= dy;

        for (x = 0; x < S_W; x++)
        {
            int dx = x - center_x;
            int distance_squared = dx * dx + dy;
            
            double normalized_distance = sqrt(distance_squared) * inv_max_distance;
            if (normalized_distance > 1.0)
                normalized_distance = 1.0;

            int lut_index = (int)(normalized_distance * (LUT_SIZE - 1));
            double bright_factor = pow_lut[lut_index];

            int r = (int)(bright_factor * r_ceiling);
            int g = (int)(bright_factor * g_ceiling);
            int b = (int)(bright_factor * b_ceiling);

            int gradient_color = (r << 16) | (g << 8) | b;
            ft_pixel_put(data, x, y, gradient_color);
        }
    }
}
static double get_wall_height(t_ray *ray, t_player ply)
{
    double dis_player;
    double wall_height;
    double distance;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);
    distance = ray->distance * cos(ply.angle - ray->ray_ngl);
    wall_height = (dis_player * TILE_SIZE) / distance;
    return wall_height;
}

t_wall_params calculate_wall_params(t_data *data)
{
    t_wall_params params;
    int look_offset;

    look_offset = data->ply->look_offset;
    params.wall_height = get_wall_height(data->ray, *data->ply);
    params.start_y = (S_H / 2) - ((int)params.wall_height / 2) + look_offset;
    params.end_y = (S_H / 2) + ((int)params.wall_height / 2) + look_offset;
    params.save_y = params.start_y;
    if (params.start_y < 0)
        params.start_y = 0;
    if (params.end_y >= S_H)
        params.end_y = S_H - 1;
    if (params.end_y >= S_H)
        params.end_y = S_H - 1;
    return params;
}

void render_wall(t_data *data, int x, double ray_angle)
{
    int texture_x, texture_y;
    double brightness_factor;
    t_wall_params wall_params;

    wall_params = calculate_wall_params(data);
    texture_x = get_start_drawing_texture_x(*data->ray);
    brightness_factor = 1.0 - (data->ray->distance / (TILE_SIZE * 12));
    t_texture *texture = selected_texture(data, *data->ray, ray_angle);
    while (wall_params.start_y <= wall_params.end_y)
    {
        texture_y = ((wall_params.start_y - wall_params.save_y) * 576) / wall_params.wall_height;
        int color = get_pixel(texture, texture_x, texture_y);
        if (color || color != BLK)
        {
            int r = ((color >> 16) & 0xFF) * brightness_factor;
            r = clamp(r, 0, 255);
            int g = ((color >> 8) & 0xFF) * brightness_factor;
            g = clamp(g, 0, 255);
            int b = (color & 0xFF) * brightness_factor;
            b = clamp(b, 0, 255);
            color = (r << 16) | (g << 8) | b;
            ft_pixel_put(data, x, wall_params.start_y, color);
        }
        wall_params.start_y++;
    }
}
void drawing_3d_game(t_data *data)
{
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
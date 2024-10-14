#include "../../includes/renderer.h"

// void draw_sky_floor(t_data *data)
// {
//     int x, y;
//     int center_x = S_W / 2;
//     int center_y_sky = (S_H / 2) + data->ply->look_offset; // Adjust sky based on look_offset   
//     int max_distance = sqrt((S_W / 2) * (S_W / 2) + S_H * S_H); // Max distance from center

//     for (y = 0; y < S_H; y++)
//     {
//         for (x = 0; x < S_W; x++)
//         {
//             if (y < S_H / 2 + data->ply->look_offset) // Adjust sky rendering based on look_offset
//             {
//                 double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y_sky) * (y - center_y_sky));
//                 double normalized_distance = distance / max_distance;
//                 if (normalized_distance > 1.0)
//                     normalized_distance = 1.0;

//                 double bright_factor = pow(normalized_distance, 3);
//                 int r = (int)((1.0 - bright_factor) * 0 + bright_factor * data->args->Ceiling_color.r);
//                 int g = (int)((1.0 - bright_factor) * 0 + bright_factor * data->args->Ceiling_color.g);
//                 int b = (int)((1.0 - bright_factor) * 0 + bright_factor * data->args->Ceiling_color.b);
//                 int gradient_color = (r << 16) | (g << 8) | b;
//                 ft_pixel_put(data, x, y, gradient_color);
//             }
//         }
//     }
// }
void draw_sky_floor(t_data *data)
{
    int x, y;
    int center_x = S_W / 2;
    int center_y_sky = (S_H / 2) + data->ply->look_offset;
    int max_distance_squared = (S_W / 2) * (S_W / 2) + S_H * S_H;
    double inv_max_distance = 1.0 / sqrt(max_distance_squared);

    // Precompute color components
    int r_ceiling = data->args->Ceiling_color.r;
    int g_ceiling = data->args->Ceiling_color.g;
    int b_ceiling = data->args->Ceiling_color.b;

    // Precompute lookup table for pow(x, 3)
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
t_texture *get_wall_frame(t_data data)
{
    return (data.textures.wall_frame1);
}
int check_wall_frame(t_data data)
{
    int i;
    int j;

    i = data.ray->min_inter.xintercept / TILE_SIZE;
    j = data.ray->min_inter.yintercept / TILE_SIZE;
    if (i >= data.w_map || j >= data.h_map || i < 0 || j < 0)
        return 0;
    if (data.map2d[j][i] == 'F')
        return 1;
    return (0);
}
static t_texture *selected_texture(t_data *data, t_ray ray, float ray_angle)
{
    if (ray.v_or_h == 1)
    {
        if (isRayFacingUp(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data));
            return data->textures.wall_NO;  // NO texture
        }
        else if (isRayFacingDown(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data));
            return data->textures.wall_SO;  // SO texture
        }
    }
    else
    {
        if (isRayFacingLeft(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data));
            return data->textures.wall_WE;  // WE texture
        }
        else if (isRayFacingRight(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data));
            return data->textures.wall_EA;  // EA texture
        }
    }
    return NULL;
}
t_texture *texture_loader(t_data *data, char *texture_path)
{
    t_texture *texture = malloc(sizeof(t_texture));
    if (!texture)
        ft_error("Memory allocation failed");
    texture->img = mlx_xpm_file_to_image(data->mlx->mlx, texture_path, &texture->width, &texture->height);
    if (!texture->img)
        ft_error("Texture loading failed");
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    return (texture);
}
int get_pixel_from_texture(t_texture *texture, int offset_x, int offset_y)
{
    int pixel_offset;   

    if (texture == NULL)
        return (0);
    if (offset_x < 0 || offset_x >= texture->width || offset_y < 0 || offset_y >= texture->height)
        return 0; // Return a default color (like black) if out of bounds

    pixel_offset = (offset_y * texture->line_length) + (offset_x * (texture->bits_per_pixel / 8));

    int color = *(int *)(texture->addr + pixel_offset);
    return color;
}
int get_start_drawing_texture_x(t_ray ray)
{
    int offset;

    if (ray.v_or_h == 1) // Horizontal hit
    {
        offset = (int)ray.min_inter.xintercept % TILE_SIZE;
    }
    else // Vertical hit
    {
        offset = (int)ray.min_inter.yintercept % TILE_SIZE;
    }
    return offset;
}
static double get_wall_height(t_ray *ray, t_player ply)
{
    double dis_player;
    double wall_height;
    double distance;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);   // Distance from player to projection plane 
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
int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
void render_wall(t_data *data, int x)
{
    int texture_x, texture_y;
    double brightness_factor;
    t_wall_params wall_params;

    wall_params = calculate_wall_params(data);
    texture_x = get_start_drawing_texture_x(*data->ray);
    brightness_factor = 1.0 - (data->ray->distance / (TILE_SIZE * 12));
    t_texture *texture = selected_texture(data, *data->ray, data->ray->ray_ngl);
    while (wall_params.start_y <= wall_params.end_y)
    {
        texture_y = ((wall_params.start_y - wall_params.save_y) * 576) / wall_params.wall_height;
        int color = get_pixel_from_texture(texture, texture_x, texture_y);
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
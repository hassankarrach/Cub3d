#include "../includes/cub3d.h"
#include <stdlib.h> // For rand()

void draw_sky_floor(t_data *data)
{
    int x, y;
    int center_x = S_W / 2;
    int center_y = S_H;                                         // Bottom center of the screen
    int max_distance = sqrt((S_W / 2) * (S_W / 2) + S_H * S_H); // Max distance from the bottom center

    // Draw the sky and floor
    for (y = 0; y < S_H; y++)
    {
        for (x = 0; x < S_W; x++)
        {
            if (y < S_H / 2) // Draw sky
            {
                // Calculate distance from the center of the gradient (bottom center for sky)
                double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));

                // Normalize distance to a value between 0 and 1
                double normalized_distance = distance / max_distance;
                if (normalized_distance > 1.0)
                    normalized_distance = 1.0;

                // Amplify the brightening effect at the edges
                double bright_factor = pow(normalized_distance, 3); // Cubing to brighten more rapidly

                // Interpolate between dark blue and bright blue based on bright_factor
                int r = (int)((1.0 - bright_factor) * 1 + bright_factor *  31);   // From dark blue (0) to bright blue (135)
                int g = (int)((1.0 - bright_factor) * 32 + bright_factor * 67);   // From dark blue (0) to bright blue (206)
                int b = (int)((1.0 - bright_factor) * 71 + bright_factor * 149); // From dark blue (139) to bright blue (250)

                // Combine RGB values into a single integer (assuming 0xRRGGBB format)
                int gradient_color = (r << 16) | (g << 8) | b;

                // Draw the pixel with the calculated gradient color
                ft_pixel_put(data, x, y, gradient_color);
            }
            else // Draw floor
            {
                // Calculate distance from the center of the gradient
                double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));

                // Normalize distance to a value between 0 and 1
                double normalized_distance = distance / max_distance;
                if (normalized_distance > 1.0)
                    normalized_distance = 1.0;

                // Amplify the darkening effect at the edges more significantly
                double dark_factor = pow(normalized_distance, 0.7); // Cubing to darken more rapidly

                // Interpolate between the color ORNG and black based on dark_factor
                int r = (int)((1.0 - dark_factor) * 255 + dark_factor * 0); // From orange (255) to black (0)
                int g = (int)((1.0 - dark_factor) * 165 + dark_factor * 0); // From orange (165) to black (0)
                int b = (int)((1.0 - dark_factor) * 0 + dark_factor * 0);   // From orange (0) to black (0)

                // Combine RGB values into a single integer (assuming 0xRRGGBB format)
                int gradient_color = (r << 16) | (g << 8) | b;

                // Draw the pixel with the calculated gradient color
                ft_pixel_put(data, x, y, gradient_color);
            }
        }
    }
}


int selected_texture(t_data *data, float ray_angle)
{
    char *selected_texture;

    if (data->ray->v_or_h == 1)
    {
        if (isRayFacingUp(ray_angle))
            return (RED);
        else if (isRayFacingDown(ray_angle))
            return (GREN);
    }
    else
    {
        if (isRayFacingLeft(ray_angle))
            return (BLK);
        else if (isRayFacingRight(ray_angle))
            return (WHI);
    }
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
    int color;

    if (offset_x < 0 || offset_x >= texture->width || offset_y < 0 || offset_y >= texture->height)
        return 0;

    pixel_offset = (offset_y * texture->line_length) + (offset_x * (texture->bits_per_pixel / 8));
    color = *(int *)(texture->addr + pixel_offset);
    return color;
}
int get_texture_offset(t_data *data, float ray_angle)
{
    int offset;

    if (data->ray->v_or_h == 1) // Horizontal hit
    {
        offset = (int)data->ray->h_x % TILE_SIZE;
    }
    else // Vertical hit
    {
        offset = (int)data->ray->v_y % TILE_SIZE;
    }
    return offset;
}

void render_wall(t_data *data, double distance, int x, double ray_angl)
{
    double dis_player;
    int start_y;
    int end_y;
    int save_y;
    int texture_x, texture_y;
    double brightness_factor;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2); // distance fropm player to pr plane 
    distance = distance * cos(ray_angl - data->ply->angle); // corrected distance
    data->ray->wall_height = (dis_player * TILE_SIZE) / distance;      // projected wall height
    start_y = (S_H / 2) - ((int)data->ray->wall_height / 2);
    end_y = (S_H / 2) + ((int)data->ray->wall_height / 2);
    save_y = start_y;
    texture_x = (get_texture_offset(data, ray_angl) * 576) / TILE_SIZE;

    brightness_factor = fmax(1.0 - (distance / (TILE_SIZE * 15)), 0.2);

    while (start_y <= end_y)
    {
        // Calculate texture Y
        texture_y = ((start_y - save_y) * 576) / data->ray->wall_height;
        int color = get_pixel_from_texture(data->texture1, texture_x, texture_y);
        int r = ((color >> 16) & 0xFF) * brightness_factor;
        int g = ((color >> 8) & 0xFF) * brightness_factor;
        int b = (color & 0xFF) * brightness_factor;
        color = (r << 16) | (g << 8) | b;
        ft_pixel_put(data, x, start_y, color);
        start_y++;
    }
}
void drawing_3d_game(t_data *data)
{
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
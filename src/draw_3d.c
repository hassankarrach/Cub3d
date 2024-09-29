#include "../includes/cub3d.h"
#include <stdlib.h> // For rand()

void draw_sky_floor(t_data *data)
{
    int x, y;
    int center_x = S_W / 2;
    int center_y_sky = (S_H / 2) + data->ply->look_offset; // Adjust sky based on look_offset
    int center_y_floor = (S_H / 2) + data->ply->look_offset; // Adjust floor based on look_offset
    int max_distance = sqrt((S_W / 2) * (S_W / 2) + S_H * S_H); // Max distance from center

    for (y = 0; y < S_H; y++)
    {
        for (x = 0; x < S_W; x++)
        {
            if (y < S_H / 2 + data->ply->look_offset) // Adjust sky rendering based on look_offset
            {
                double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y_sky) * (y - center_y_sky));
                double normalized_distance = distance / max_distance;
                if (normalized_distance > 1.0)
                    normalized_distance = 1.0;

                double bright_factor = pow(normalized_distance, 3);
                int r = (int)((1.0 - bright_factor) * 0 + bright_factor * 1);
                int g = (int)((1.0 - bright_factor) * 0 + bright_factor * 32);
                int b = (int)((1.0 - bright_factor) * 0 + bright_factor * 71);
                int gradient_color = (r << 16) | (g << 8) | b;
                ft_pixel_put(data, x, y, gradient_color);
            }
            else if (y > S_H / 2 + data->ply->look_offset) // Adjust floor rendering based on look_offset
            {
                double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y_floor) * (y - center_y_floor));
                double normalized_distance = distance / max_distance;
                if (normalized_distance > 1.0)
                    normalized_distance = 1.0;

                double dark_factor = pow(normalized_distance, 0.7);
                int r = (int)(dark_factor * 59);
                int g = (int)(dark_factor * 8);
                int b = (int)(dark_factor * 4);
                int gradient_color = (r << 16) | (g << 8) | b;
                ft_pixel_put(data, x, y, gradient_color);
            }
        }
    }
}

t_texture *selected_texture(t_data *data, float ray_angle) {
    if (data->ray->v_or_h == 1) {
        if (isRayFacingUp(ray_angle))
            return data->texture1;  // NO texture
        else if (isRayFacingDown(ray_angle))
            return data->texture2;  // SO texture
    } else {
        if (isRayFacingLeft(ray_angle))
            return data->texture3;  // WE texture
        else if (isRayFacingRight(ray_angle))
            return data->texture4;  // EA texture
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

    if (offset_x < 0 || offset_x >= texture->width || offset_y < 0 || offset_y >= texture->height)
        return 0; // Return a default color (like black) if out of bounds

    pixel_offset = (offset_y * texture->line_length) + (offset_x * (texture->bits_per_pixel / 8));

    int color = *(int *)(texture->addr + pixel_offset);
    return color;
}
int get_start_drawing_texture_x(t_data *data, float ray_angle)
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
    double wall_height;
    int start_y;
    int end_y;
    int save_y;
    int texture_x, texture_y;
    double brightness_factor;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);   // distance fropm player to pr plane
    distance = distance * cos(data->ply->angle - ray_angl); // corrected distance
    wall_height = (dis_player * TILE_SIZE) / distance;      // projected wall height
    start_y = (S_H / 2) - ((int)wall_height / 2) + data->ply->look_offset;
    end_y = (S_H / 2) + ((int)wall_height / 2) + data->ply->look_offset;
    save_y = start_y;
    if (start_y < 0)
        start_y = 0;
    if (end_y >= S_H)
        end_y = S_H - 1;
    texture_x = get_start_drawing_texture_x(data, ray_angl);
    brightness_factor = fmax(1.0 - (distance / (TILE_SIZE * 4)), 0.2);
    while (start_y <= end_y)
    {
        texture_y = ((start_y - save_y) * 576) / wall_height;
        int color = get_pixel_from_texture(selected_texture(data, ray_angl), texture_x, texture_y);
        // int color = selected_texture(data, ray_angl);
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
    // int x;
    // int y;
    // int color;
    // static int frame = 0;
    // static int frame_delay = 0;

    // x = 0;
    // y = 0;
    // while (y < 600)
    // {
    //     x = 0;
    //     while (x < 600)
    //     {
    //         color = get_pixel_from_texture(data->player[frame], x, y);
    //         if (color != BLK)
    //             ft_pixel_put(data, x + 400, y+ 400, color);
    //         x++;
    //     }
    //     y++;
    // }
    // draw_sprites(data);
    // printf ("x = %f, y = %f\n", data->ply->posX, data->ply->posY);
    // printf ("x sprite = %f, y sprite = %f\n", data->sprites->x, data->sprites->y);
    render_mini_map(data);
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
    // frame_delay++;
    // if (frame_delay >= 2) // Adjust '5' to slow down or speed up the frame rate
    // {
    //     frame++;         // Only increment frame every few calls
    //     frame_delay = 0; // Reset the delay counter
    // }

    // // Reset frame back to 1 after reaching 13
    // if (frame == 13)
    //     frame = 1;
}
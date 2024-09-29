#include "../includes/cub3d.h"
#include <math.h> // For sqrt, cos, sin, acos

void calculate_sprite_distance(t_sprite *sprite, t_player *player)
{
    sprite->distance = sqrt(pow(sprite->x - player->posX, 2) + 
                            pow(sprite->y - player->posY, 2));
}

void scale_sprite(t_sprite *sprite)
{
    float scalingFactor = 100.0f;  // You can tweak this to adjust overall sprite size
    if (sprite->distance > 0)
        sprite->scale = scalingFactor / sprite->distance;
    else
        sprite->scale = 0; // Prevent division by zero
}

void get_direction_vector(t_player *player, double *dir_x, double *dir_y)
{
    *dir_x = cos(player->angle);  // Assuming angle is in radians
    *dir_y = sin(player->angle);
}

void calculate_vector_to_sprite(t_sprite *sprite, t_player *player, double *vec_to_sprite_x, double *vec_to_sprite_y)
{
    *vec_to_sprite_x = sprite->x - player->posX;
    *vec_to_sprite_y = sprite->y - player->posY;
}

double dot_product(double dir_x, double dir_y, double vec_to_sprite_x, double vec_to_sprite_y)
{
    return (dir_x * vec_to_sprite_x) + (dir_y * vec_to_sprite_y);
}

bool is_player_facing_sprite(t_player *player, t_sprite *sprite, double threshold_angle)
{
    double dir_x, dir_y;
    double vec_to_sprite_x, vec_to_sprite_y;

    get_direction_vector(player, &dir_x, &dir_y);
    calculate_vector_to_sprite(sprite, player, &vec_to_sprite_x, &vec_to_sprite_y);

    double dot = dot_product(dir_x, dir_y, vec_to_sprite_x, vec_to_sprite_y);
    double magnitude_player = sqrt(dir_x * dir_x + dir_y * dir_y);
    double magnitude_sprite = sqrt(vec_to_sprite_x * vec_to_sprite_x + vec_to_sprite_y * vec_to_sprite_y);

    double cosine_angle = dot / (magnitude_player * magnitude_sprite);

    // Ensure cosine_angle is within the range of acos function
    if (cosine_angle < -1.0) cosine_angle = -1.0;
    if (cosine_angle > 1.0) cosine_angle = 1.0;

    // Calculate the angle in radians
    double angle = acos(cosine_angle);

    // Check if the angle is within the threshold
    return angle < threshold_angle;
}

void draw_sprite(t_data *data, t_sprite *sprite, int screenX, int screenY)
{
    int sprite_width = 225 * sprite->scale;
    int sprite_height = 225 * sprite->scale;

    // Draw the sprite on the screen using your existing texture drawing logic
    for (int y = 0; y < sprite_height; y++) {
        for (int x = 0; x < sprite_width; x++) {
            int texture_x = (int)(x / sprite->scale);
            int texture_y = (int)(y / sprite->scale);
            int color = get_pixel_from_texture(sprite->texture, texture_x, texture_y);
            if (color != BLK) { // Ensure to define TRANSPARENT_COLOR
                ft_pixel_put(data, screenX + x, screenY + y, color);
            }
        }
    }
}

void render_sprites(t_data *data)
{
    t_sprite *sprite = data->sprites;

    // Define a threshold angle for facing check (e.g., 45 degrees)
    double threshold_angle = M_PI / 4; // 45 degrees in radians

    // Calculate distance and scale for the sprite
    calculate_sprite_distance(sprite, data->ply);
    scale_sprite(sprite);

    // Check if the player is facing the sprite before drawing
    if (is_player_facing_sprite(data->ply, sprite, threshold_angle))
    {
        // Calculate the relative position of the sprite in the player's coordinate space
        double relative_x = sprite->x - data->ply->posX;
        double relative_y = sprite->y - data->ply->posY;

        // Calculate the angle of the sprite relative to the player
        double angle_to_sprite = atan2(relative_y, relative_x) - data->ply->angle;

        // Get the distance to the sprite
        double distance = sqrt(relative_x * relative_x + relative_y * relative_y);

        // Assuming a fixed FOV and screen size
        double fov = M_PI / 3; // Example: 60 degrees
        double screen_center = S_W / 2;

        // Project the sprite onto the screen using the angle and distance
        int screenX = (int)(screen_center + (distance * cos(angle_to_sprite)) * (screen_center / tan(fov / 2)));
        int screenY = (int)(S_H / 2 + (distance * sin(angle_to_sprite)) * (screen_center / tan(fov / 2)));

        // Adjust for sprite scale
        screenX -= (sprite->width * sprite->scale) / 2; // Centering sprite width
        screenY -= (sprite->height * sprite->scale) / 2; // Centering sprite height

        draw_sprite(data, sprite, screenX, screenY);
    }
}

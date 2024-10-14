#include "../../includes/renderer.h"

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
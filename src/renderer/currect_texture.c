#include "../../includes/renderer.h"

t_wallFrame *get_currect_texture(t_wallFrame **wall_frame, int i, int j)
{
    int n;

    n = 0;
    while (wall_frame[n] != NULL)
    {
        if (wall_frame[n]->x == i && wall_frame[n]->y == j)
            return wall_frame[n];
        n++;
    }
    return (NULL);
}

t_texture *get_wall_frame(t_data data, e_Direction direction, t_texture *texture_wall)
{
    t_wallFrame *wall_frame;
    int i;
    int j;

    i = (int)data.ray->min_inter.xintercept / TILE_SIZE;
    j = (int)data.ray->min_inter.yintercept / TILE_SIZE;
    if (i >= data.w_map || j >= data.h_map || i < 0 || j < 0)
        return NULL;
    wall_frame = get_currect_texture(data.args->frames, i, j);
    if (wall_frame == NULL)
        return texture_wall;
    if (wall_frame->direction == direction)
    {
        if (wall_frame->Frame == 1)
            return (data.textures.wall_frame1);
        else
            return (data.textures.wall_frame2);
    }
    return (texture_wall);
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

t_texture *selected_texture(t_data *data, t_ray ray, float ray_angle)
{
    t_texture *texture;

    if (ray.v_or_h == 1)
    {
        if (isRayFacingUp(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data, TOP, data->textures.wall_NO));
            return data->textures.wall_NO;  // NO texture
        }
        else if (isRayFacingDown(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data, BOTTOM, data->textures.wall_SO));
            return data->textures.wall_SO;  // SO texture
        }
    }
    else
    {
        if (isRayFacingLeft(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data, LEFT, data->textures.wall_WE));
            return data->textures.wall_WE;  // WE texture
        }
        else if (isRayFacingRight(ray_angle))
        {
            if (check_wall_frame(*data))
                return (get_wall_frame(*data, RIGHT, data->textures.wall_EA));
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
#include "../includes/cub3d.h"
void draw_sky_floor(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < S_H)
    {
        x = 0;
        while (x < S_W)
        {
            if (y < S_H / 2)
                ft_pixel_put(data, x, y, BLU);
            else
                ft_pixel_put(data, x, y, ORNG);
            x++;
        }
        y++;
    }
}
// char *render_wall(t_data *data, float ray_angle, t_tex *textures)
// {
//     char *selected_texture;

//     if (is_ray_facing_up(ray_angle))
//         selected_texture = textures->north;
//     else if (is_ray_facing_down(ray_angle))
//         selected_texture = textures->south;
//     else if (is_ray_facing_left(ray_angle))
//         selected_texture = textures->west;
//     else if (is_ray_facing_right(ray_angle))
//         selected_texture = textures->east;
//     return (selected_texture);
// }
// int selected_texture(float ray_angle)
// {
//     char *selected_texture;

//     if (isRayFacingUp(ray_angle))
//         return (RED);
//     else if (isRayFacingDown(ray_angle))
//         return (GREN);
//     else if (isRayFacingLeft(ray_angle))
//         return (BLK);
//     else if (isRayFacingRight(ray_angle))
//         return (WHI);
// }


void render_wall(t_data *data, double distance, int x, double ray_angl)
{
    double dis_player; // dist frome player to pro.plane
    double wall_height; 
    int start_y;
    int end_y;
    int color;
    // char *selected_texture;

    dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);
    distance = distance * cos(ray_angl -  data->ply->angle); // corrected distance 
    wall_height = (dis_player * TILE_SIZE) / distance; // find projection wall height
    start_y = (S_H / 2) - ((int)wall_height / 2);
    end_y = (S_H / 2) + ((int)wall_height / 2);
    while(start_y <= end_y)
    {
        ft_pixel_put(data, x, start_y, RED);
        start_y++;
    }
}
void drawing_3d_game(t_data *data)
{
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
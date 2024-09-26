#include "../includes/cub3d.h"

void calculate_sprite_distances(t_data *data, t_sprite *sprite)
{
    sprite->distance = ((data->ply->posX - sprite->x) * (data->ply->posX - sprite->x)) +
                       ((data->ply->posY - sprite->y) * (data->ply->posY - sprite->y));
}
void calculate_transform(t_data *data, t_sprite sprite, double *transform_x, double *transform_y)
{
    double	inv_det;
	t_sprite	normalized_sprite;

	normalized_sprite.x = sprite.x - data->ply->posX;
	normalized_sprite.y = sprite.y - data->ply->posY;
	inv_det = 1.0 / (data->ply->plane_x * data->ply->dir_y - data->ply->dir_x * data->ply->plane_y);
	*transform_x = inv_det * (data->ply->dir_y * normalized_sprite.x - data->ply->dir_x * normalized_sprite.y);
	*transform_y = inv_det * (-data->ply->plane_y * normalized_sprite.x + data->ply->plane_x * normalized_sprite.y);
}
 void	calc_sprite_vis(t_data *data, t_sprite *sprite)
{
	calculate_transform(data, *sprite, &sprite->transform_x, &sprite->transform_y);
	sprite->screen_x = (int)((S_W / 2) *
		(1.0 + sprite->transform_x / sprite->transform_y));
	sprite->height = abs((int)(100.0 / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + S_H / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + S_H / 2;
	sprite->draw_end_y = (sprite->draw_end_y >= S_H) ? S_H - 1 : sprite->draw_end_y;
	sprite->width = abs((int)(100.0 / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end_x >= S_W)
		sprite->draw_end_x = S_W - 1;
}
static int	calc_tex_x(t_data *data, t_sprite  sprite_vis, int x)
{
	return ((int)((x - (-sprite_vis.width / 2 + sprite_vis.screen_x)) *
			576 / sprite_vis.width));
}

static int	calc_tex_y(t_data *data, t_sprite  sprite_vis, int y)
{
	return ((int)((y - (-sprite_vis.height / 2 + S_W / 2)) *
					576 / sprite_vis.height));
}

void		draw_sprite_stripe(t_data *data, t_sprite  sprite_vis)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;

	x = sprite_vis.draw_start_x;
	while (x < sprite_vis.draw_end_x)
	{
		tex_x = calc_tex_x(data, sprite_vis, x);
			y = sprite_vis.draw_start_y;
			while (y < sprite_vis.draw_end_y)
			{
				tex_y = calc_tex_y(data, sprite_vis, y);
				if (!(get_pixel_from_texture(data->texture1, tex_x, tex_y) & 0xff000000))
					mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, get_pixel_from_texture(data->texture1, tex_x, tex_y));
				y++;
			}
		x++;
	}
}
void		draw_sprites(t_data *data)
{
	calc_sprite_vis(data, data->sprites);
	draw_sprite_stripe(data, *data->sprites);
}


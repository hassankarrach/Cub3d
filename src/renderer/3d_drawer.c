/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:54:09 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/08 21:27:37 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

void	draw_sky_floor(t_data *data)
{
	int				x;
	int				y;
	t_sky_params	params;
	double			norm_dist;
	int				color;

	y = 0;
	params.center_x = S_W / 2;
	params.center_y_sky = (S_H / 2) + data->ply->look_offset;
	params.max_distance = sqrt((S_W / 2) * (S_W / 2) + S_H * S_H);
	while (y < S_H / 2 + data->ply->look_offset)
	{
		x = 0;
		while (x < S_W)
		{
			norm_dist = calculate_normalized_distance(x, y, &params);
			color = calculate_sky_color(norm_dist);
			ft_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

static double	get_wall_height(t_ray *ray, t_player ply)
{
	double	dis_player;
	double	wall_height;
	double	distance;

	dis_player = (S_W / 2) / tan((ply.fov_rd) / 2);
	distance = ray->distance * cos(ply.angle - ray->ray_ngl);
	wall_height = (dis_player * TILE_SIZE) / distance;
	return (wall_height);
}

t_wall_params	calculate_wall_params(t_data *data)
{
	t_wall_params	params;
	int				look_offset;

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
	return (params);
}

void	render_wall(t_data *data, int x, double ray_angle)
{
	double			brightness_factor;
	t_wall_params	wall_params;
	t_texture		*texture;
	int				color;

	wall_params = calculate_wall_params(data);
	wall_params.texture_x = get_start_drawing_texture_x(*data->ray);
	brightness_factor = 1.0 - (data->ray->distance / (TILE_SIZE * 12));
	texture = selected_texture(data, *data->ray, ray_angle);
	while (wall_params.start_y <= wall_params.end_y)
	{
		wall_params.texture_y = ((wall_params.start_y - \
			wall_params.save_y) * 576) / wall_params.wall_height;
		color = get_pixel(texture, wall_params.texture_x, \
			wall_params.texture_y);
		if (color || color != BLK)
		{
			color = adjust_color_opacity2(color, brightness_factor);
			ft_pixel_put(data, x, wall_params.start_y, color);
		}
		wall_params.start_y++;
	}
}

void	drawing_3d_game(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img, 0, 0);
}

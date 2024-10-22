/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:03:55 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/22 05:09:24 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

void	update_door_animation(t_data *data, t_door *door, double current_time)
{
	t_wall_door	*corret_door;

	corret_door = get_corret_door(data, door->doors);
	if (!corret_door)
		return ;
	if (current_time - door->last_update_time >= DOOR_ANIMATION_FRAME_TIME)
	{
		if (corret_door->is_open
			&& corret_door->current_frame < door->total_frames - 1)
			corret_door->current_frame++;
		else if (!corret_door->is_open && corret_door->current_frame)
			corret_door->current_frame--;
		door->last_update_time = current_time;
	}
	door->current_frame = corret_door->current_frame;
}
t_wall_params	calculate_door_params(t_data *data)
{
	t_wall_params	params;

	params.wall_height = get_door_height(data->door, data->ray, *data->ply);
	params.start_y = (S_H / 2) - ((int)params.wall_height / 2)
		+ data->ply->look_offset;
	params.end_y = (S_H / 2) + ((int)params.wall_height / 2)
		+ data->ply->look_offset;
	params.save_y = params.start_y;
	if (params.start_y < 0)
		params.start_y = 0;
	if (params.end_y >= S_H)
		params.end_y = S_H - 1;
	if (params.end_y >= S_H)
		params.end_y = S_H - 1;
	return (params);
}

int	apply_brightness(int color, double brightness_factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * brightness_factor;
	r = clamp(r, 0, 255);
	g = ((color >> 8) & 0xFF) * brightness_factor;
	g = clamp(g, 0, 255);
	b = (color & 0xFF) * brightness_factor;
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

void	rendring_door(t_data *data, t_door door, int x)
{
	t_wall_params	wall_params;
	t_texture		*texture;
	int				color;

	wall_params = calculate_door_params(data);
	wall_params.texture_x = get_start_drawing_texture_x_door(*data->door);
	wall_params.brightness_factor = 1.0 - (door.distance / (TILE_SIZE * 12));
	texture = selected_texture_door(data, *data->ray);
	while (wall_params.start_y <= wall_params.end_y)
	{
		wall_params.texture_y = ((wall_params.start_y - wall_params.save_y)
				* 576) / wall_params.wall_height;
		color = get_pixel(texture, wall_params.texture_x,
				wall_params.texture_y);
		if (color != 0 && color != BLK)
		{
			color = apply_brightness(color, wall_params.brightness_factor);
			ft_pixel_put(data, x, wall_params.start_y, color);
		}
		wall_params.start_y++;
	}
}

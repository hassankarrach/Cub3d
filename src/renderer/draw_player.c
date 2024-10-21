/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 04:32:08 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 04:38:04 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

void	update_ply_animation(t_data *data, t_player *ply, double current_time)
{
	double	time_between_frames;

	time_between_frames = 0.03;
	if (data->ply->move_speed != 1)
		time_between_frames = 0;
	if (current_time - ply->last_update_time >= time_between_frames)
	{
		if (ply->current_frame < ply->total_frames - 1)
			ply->current_frame++;
		ply->last_update_time = current_time;
		if (ply->current_frame + 1 >= ply->total_frames)
			ply->current_frame = 0;
	}
}

void	draw_player(t_data *data, double current_time)
{
	int	start_y;
	int	x;
	int	y;
	int	color;

	if (!data->ply->walk_direction)
		return ;
	x = 0;
	start_y = S_H - data->textures.player[0]->height + data->ply->look_offset;
	if (start_y < S_H - data->textures.player[0]->height)
		start_y = S_H - data->textures.player[0]->height;
	y = start_y - 1;
	while (++y < S_H)
	{
		x = -1;
		while (++x < S_W)
		{
			if (x > 220 && x < 780)
				x += 560;
			color = get_pixel(data->textures.player[data->ply->current_frame], \
				x, y - start_y);
			if (color != BLK && color)
				ft_pixel_put(data, x, y, color);
		}
	}
}

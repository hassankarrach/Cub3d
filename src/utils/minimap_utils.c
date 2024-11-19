/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:29:08 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/19 03:34:51 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	draw_player_icon(t_data *data)
{
	int				x;
	int				y;
	int				start_x;
	int				start_y;
	unsigned int	color;

	start_x = ((S_W_MINI_MAP + 16) / 2) - (32 / 2);
	start_y = ((S_H_MINI_MAP + 14) / 2) - (32 / 2);
	x = 0;
	y = 0;
	while (y < data->textures.icon_player->height)
	{
		x = 0;
		while (x < data->textures.icon_player->width)
		{
			color = get_pixel(data->textures.icon_player, x, y);
			if (color != BLK)
				ft_pixel_put(data, x + start_x, y + start_y, color);
			x++;
		}
		y++;
	}
}

static void	set_pixels_img(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	x = 0;
	y = 0;
	while (x < S_W_MINI_MAP + 14)
	{
		y = 0;
		while (y < S_H_MINI_MAP + 14)
		{
			color = get_pixel(data->textures.mini_map, x, y);
			if (color != BLK)
				ft_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

static void	render_mini_map_row(t_data *data, int x)
{
	int		y;
	int		color;
	float	fade_factor;
	int		faded_color;
	float	distance_ratio;

	y = 14;
	while (y < S_H_MINI_MAP)
	{
		color = pos_to_color(data, x, y);
		if (color != -1)
		{
			distance_ratio = sqrt(pow(x - S_W_MINI_MAP / 2, 2)
					+ pow(y - S_H_MINI_MAP / 2, 2))
				/ sqrt(pow(S_W_MINI_MAP / 2, 2) + pow(S_H_MINI_MAP / 2, 2));
			fade_factor = 1.0 - (distance_ratio * 0.5);
			faded_color = adjust_color_opacity2(color, fade_factor);
			ft_pixel_put(data, x, y, faded_color);
		}
		y++;
	}
}

void	render_mini_map(t_data *data)
{
	int	x;

	x = 16;
	set_pixels_img(data);
	while (x < S_W_MINI_MAP)
	{
		render_mini_map_row(data, x);
		x++;
	}
	draw_player_icon(data);
}

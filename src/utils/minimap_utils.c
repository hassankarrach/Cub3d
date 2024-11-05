/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:29:08 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/06 00:29:56 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	draw_player_icon(t_data *data)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	color;

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
	int	x;
	int	y;
	int	color;

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

int	adjust_color_opacity2(int color, double fade_factor)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * fade_factor;
	r = clamp(r, 0, 255);
	g = g * fade_factor;
	g = clamp(g, 0, 255);
	b = b * fade_factor;
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

void	render_mini_map(t_data *data)
{
	int	x;
	int	y;

	set_pixels_img(data);
	x = 16;
	while (x < S_W_MINI_MAP)
	{
		y = 14;
		while (y < S_H_MINI_MAP)
		{
			render_pixel(data, x, y);
			y++;
		}
		x++;
	}
	draw_player_icon(data);
}

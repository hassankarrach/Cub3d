/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:10:21 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 02:12:06 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

static int	adjust_color_opacity(t_rgb Floor_color, float brightness_factor)
{
	int	r;
	int	g;
	int	b;

	r = (Floor_color.r) * brightness_factor;
	r = clamp(r, 0, 255);
	g = (Floor_color.g) * brightness_factor;
	g = clamp(g, 0, 255);
	b = (Floor_color.b) * brightness_factor;
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

void	floor_casting(t_data *data, int x)
{
	int		y;
	int		color;
	double	row_distance;
	float	brightness_factor;

	y = S_H / 2 + data->ply->look_offset;
	while (y < S_H)
	{
		row_distance = (double)(y - S_H / 2 - data->ply->look_offset);
		brightness_factor = (1.0) - (1.0 / (row_distance * 0.015));
		x = 0;
		while (x < S_W)
		{
			color = adjust_color_opacity(data->args->Floor_color, \
					brightness_factor);
			ft_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

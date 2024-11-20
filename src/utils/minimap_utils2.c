/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:24:37 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/20 19:55:14 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	adjust_color_opacity2(int color, float fade_factor)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * fade_factor);
	r = clamp(r, 0, 255);
	g = (int)(g * fade_factor);
	g = clamp(g, 0, 255);
	b = (int)(b * fade_factor);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

static float	get_rotated_x(t_data *data, int x, int y)
{
	float	relative_x;
	float	relative_y;
	float	player_x;
	float	angle;

	relative_x = x - (S_W_MINI_MAP / 2);
	relative_y = y - (S_H_MINI_MAP / 2);
	player_x = (data->ply->pos_x / TILE_SIZE) * data->increase;
	angle = data->ply->angle + M_PI / 2;
	return (cos(angle) * relative_x - sin(angle) * relative_y + player_x);
}

static float	get_rotated_y(t_data *data, int x, int y)
{
	float	relative_x;
	float	relative_y;
	float	player_y;
	float	angle;

	relative_x = x - (S_W_MINI_MAP / 2);
	relative_y = y - (S_H_MINI_MAP / 2);
	player_y = (data->ply->pos_y / TILE_SIZE) * data->increase;
	angle = data->ply->angle + M_PI / 2;
	return (sin(angle) * relative_x + cos(angle) * relative_y + player_y);
}

int	pos_to_color(t_data *data, int x, int y)
{
	float	rotated_x;
	float	rotated_y;
	int		map_x;
	int		map_y;

	rotated_x = get_rotated_x(data, x, y);
	rotated_y = get_rotated_y(data, x, y);
	map_x = (int)(rotated_x / data->increase);
	map_y = (int)(rotated_y / data->increase);
	if (map_x < 0 || map_x > data->w_map || map_y < 0 || map_y > data->h_map
		|| rotated_x < 0 || rotated_y < 0)
		return (-1);
	if (data->map2d[map_y][map_x] == '1' || data->map2d[map_y][map_x] == 'F')
		return (MAP_CLR);
	if (data->map2d[map_y][map_x] == 'D')
		return (ORNG);
	if (data->map2d[map_y][map_x] == 'O')
		return (GREN);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:24:37 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/18 07:06:55 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_coord	calculate_map_coords(t_data *data, int x, int y)
{
	float	player_x;
	float	player_y;
	float	rotated_x;
	float	rotated_y;
	t_coord	coords;

	player_x = (data->ply->pos_x / TILE_SIZE) * data->increase;
	player_y = (data->ply->pos_y / TILE_SIZE) * data->increase;
	rotated_x = cos(data->ply->angle + M_PI / 2) * (x - S_W_MINI_MAP / 2)
		- sin(data->ply->angle + M_PI / 2) * (y - S_H_MINI_MAP / 2)
		+ player_x;
	rotated_y = sin(data->ply->angle + M_PI / 2) * (x - S_W_MINI_MAP / 2)
		+ cos(data->ply->angle + M_PI / 2) * (y - S_H_MINI_MAP / 2)
		+ player_y;
	coords.map_x = (int)(rotated_x / data->increase);
	coords.map_y = (int)(rotated_y / data->increase);
	return (coords);
}

int	map_tile_to_color(t_data *data, int map_x, int map_y)
{
	char	tile;

	if (map_x < 0 || map_x >= data->w_map || map_y < 0 || map_y >= data->h_map)
		return (-1);
	tile = data->map2d[map_y][map_x];
	if (tile == '1' || tile == 'F')
		return (MAP_CLR);
	if (tile == 'D')
		return (ORNG);
	if (tile == 'O')
		return (GREN);
	return (-1);
}

int	pos_to_color(t_data *data, int x, int y)
{
	t_coord	coords;

	coords = calculate_map_coords(data, x, y);
	return (map_tile_to_color(data, coords.map_x, coords.map_y));
}

float	calculate_fade_factor(int x, int y)
{
	float	distance;
	float	max_distance;

	distance = sqrt(pow(x - S_W_MINI_MAP / 2, 2)
			+ pow(y - S_H_MINI_MAP / 2, 2));
	max_distance = sqrt(pow(S_W_MINI_MAP / 2, 2) + pow(S_H_MINI_MAP / 2, 2));
	return (1.0 - (distance / max_distance * 0.5));
}

void	render_pixel(t_data *data, int x, int y)
{
	int		color;
	double	fade_factor;
	int		faded_color;

	color = pos_to_color(data, x, y);
	if (color == -1)
		return ;
	fade_factor = calculate_fade_factor(x, y);
	faded_color = adjust_color_opacity2(color, fade_factor);
	ft_pixel_put(data, x, y, faded_color);
}

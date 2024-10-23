/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:16:10 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/23 21:24:39 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	ft_distance(t_data *data, double x, double y)
{
	double	dx;
	double	dy;

	dx = x - data->ply->posX;
	dy = y - data->ply->posY;
	return (sqrt((dx * dx) + (dy * dy)));
}

int	find_wall(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = (int)floor(x / TILE_SIZE);
	j = (int)floor(y / TILE_SIZE);
	if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
		return (1);
	if (data->map2d[j][i] == '1' || data->map2d[j][i] == 'F')
		return (1);
	if (data->map2d[j][i] == 'D' || (data->map2d[j][i] == 'O'))
	{
		data->ray->hit_door = 1;
		if (data->ray->skip_door)
			return (0);
		else
			return (1);
	}
	return (0);
}

bool	player_in_grid(t_data *data)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = (int)floor(data->ply->posX / TILE_SIZE);
	player_tile_y = (int)floor(data->ply->posY / TILE_SIZE);
	if (data->map2d[player_tile_y][player_tile_x] == 'D'
		|| data->map2d[player_tile_y][player_tile_x] == 'O')
		return (true);
	else
		return (false);
}

t_inter	min_distance(t_inter inter_h, t_inter inter_v, t_data *data)
{
	double	h_dist;
	double	v_dist;

	h_dist = ft_distance(data, inter_h.xintercept, inter_h.yintercept);
	v_dist = ft_distance(data, inter_v.xintercept, inter_v.yintercept);
	if (h_dist <= v_dist)
	{
		data->ray->v_or_h = 1;
		return (inter_h);
	}
	else
	{
		data->ray->v_or_h = 0;
		return (inter_v);
	}
}

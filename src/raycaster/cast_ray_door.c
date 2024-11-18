/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:15:00 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/18 06:13:10 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

bool	is_within_map(double x, double y, t_data *data)
{
	int	i;
	int	j;

	i = (int)(x / (double)TILE_SIZE);
	j = (int)(y / (double)TILE_SIZE);
	return (i >= 0 && i < data->w_map && j >= 0 && j < data->h_map);
}

void	update_door_status(t_data *data, double currtime)
{
	float		dist_door;
	int			n;
	double		distance;

	n = 0;
	distance = 500;
	if (is_ray_facing_up(data->ply->angle))
		distance = 800;
	while (n < 3 && data->door->doors[n])
	{
		dist_door = ft_distance(data, data->door->doors[n]->i * TILE_SIZE,
				data->door->doors[n]->j * TILE_SIZE);
		if (dist_door < distance && !data->door->doors[n]->is_open)
		{
			data->door->doors[n]->is_open = 1;
			data->map2d[data->door->doors[n]->j][data->door->doors[n]->i] = 'O';
		}
		else if (dist_door > distance)
		{
			data->door->doors[n]->is_open = 0;
			data->map2d[data->door->doors[n]->j][data->door->doors[n]->i] = 'D';
		}
		update_door_animation(data, data->door, currtime, data->door->doors[n]);
		n++;
	}
}

bool	is_door(double x, double y, t_data *data)
{
	int		i;
	int		j;
	float	dist_door;

	i = (int)floor(x / (double)TILE_SIZE);
	j = (int)floor(y / (double)TILE_SIZE);
	dist_door = ft_distance(data, x, y);
	if (!is_within_map(x, y, data))
		return (false);
	return (data->map2d[j][i] == 'D' || data->map2d[j][i] == 'O');
}

void	cast_rays_door(t_data *data, int ray)
{
	t_door	*door;

	door = data->door;
	data->ray->skip_door = 0;
	door->distance = calculate_distance(data, data->ray->ray_ngl);
	door->x_intercept = data->ray->min_inter.xintercept;
	door->y_intercept = data->ray->min_inter.yintercept;
	door->is_ver_ray = data->ray->v_or_h;
	if (is_door(door->x_intercept, door->y_intercept, data) && door->is_ver_ray)
		rendring_door(data, *data->door, ray);
	data->ray->hit_door = false;
}

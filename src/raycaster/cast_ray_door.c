/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:15:00 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/23 01:13:30 by kait-baa         ###   ########.fr       */
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

void	update_door_status(t_data *data)
{
	t_wall_door	**door;
	float		dist_door;
	int n;

	n = 0;
	door = data->door->doors;
	while (n < 3 && door[n])
	{
		dist_door = ft_distance(data, door[n]->i * TILE_SIZE, door[n]->j * TILE_SIZE);
		if (dist_door < DOOR_INTERACTION_DISTANCE && !door[n]->is_open)
		{
			door[n]->is_open = 1;
			data->map2d[door[n]->j][door[n]->i] = 'O';
		}
		else if (dist_door > DOOR_INTERACTION_DISTANCE)
		{
			door[n]->is_open = 0;
			data->map2d[door[n]->j][door[n]->i] = 'D';
		}
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

bool	get_door_inter(t_data *data, t_inter *inter_h, double x_step,
		double y_step)
{
	double	save_inter_x;
	double	save_inter_y;

	save_inter_x = inter_h->xintercept;
	save_inter_y = inter_h->yintercept;
	if (player_in_grid(data))
	{
		start_h_y_door(data, data->ray->ray_ngl, &inter_h->yintercept);
		inter_h->xintercept = data->ply->posX + (inter_h->yintercept
				- data->ply->posY) / tan(data->ray->ray_ngl);
		if (fmod(data->ply->posY, TILE_SIZE) < TILE_SIZE / 2
			&& is_ray_facing_up(data->ray->ray_ngl))
		{
			inter_h->xintercept = save_inter_x;
			inter_h->yintercept = save_inter_y;
			return (false);
		}
		return (true);
	}
	inter_h->xintercept += x_step / 2;
	inter_h->yintercept += y_step / 2;
	return (false);
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

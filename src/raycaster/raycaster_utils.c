/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:15:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 03:33:02 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

static t_inter	min_distance(t_inter inter_h, t_inter inter_v, t_data *data)
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

double	calculate_distance(t_data *data, float angle)
{
	t_inter	result_inter;
	t_inter	inter_h;
	t_inter	inter_v;

	inter_h = get_h_inter(data, angle);
	inter_v = get_v_inter(data, angle);
	result_inter = min_distance(inter_h, inter_v, data);
	data->ray->min_inter.xintercept = result_inter.xintercept;
	data->ray->min_inter.yintercept = result_inter.yintercept;
	return (ft_distance(data, result_inter.xintercept,
			result_inter.yintercept));
}

void	start_h_y(t_data *data, double angl, double *h_y)
{
	if (is_ray_facing_down(angl))
		*h_y = floor(data->ply->posY / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		*h_y = floor(data->ply->posY / TILE_SIZE) * TILE_SIZE;
}

void	start_v_x(t_data *data, double angl, double *v_x)
{
	if (is_ray_facing_left(angl))
		*v_x = floor(data->ply->posX / TILE_SIZE) * TILE_SIZE;
	else
		*v_x = floor(data->ply->posX / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
}

void	start_h_y_door(t_data *data, double angl, double *h_y)
{
	double	tile_size;

	tile_size = TILE_SIZE / 2;
	if (is_ray_facing_down(angl))
		*h_y = floor(data->ply->posY / tile_size) * tile_size + tile_size;
	else
		*h_y = floor(data->ply->posY / tile_size) * tile_size;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:15:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/05 22:29:23 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

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

void	start_v_x_door(t_data *data, double angl, double *v_x)
{
	double	tile_size;

	tile_size = TILE_SIZE / 2;
	if (is_ray_facing_left(angl))
		*v_x = floor(data->ply->posX / tile_size) * tile_size;
	else
		*v_x = floor(data->ply->posX / tile_size) * tile_size + tile_size;
}

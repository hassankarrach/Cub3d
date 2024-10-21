/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:16:33 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 03:33:02 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

t_inter	get_h_inter(t_data *data, float angl)
{
	t_inter	inter_h;
	double	x_step;
	double	y_step;

	inter_h.is_door = false;
	y_step = TILE_SIZE;
	start_h_y(data, angl, &inter_h.yintercept);
	inter_h.xintercept = data->ply->posX + (inter_h.yintercept
			- data->ply->posY) / tan(angl);
	if (is_ray_facing_up(angl))
		y_step *= -1;
	x_step = y_step / tan(angl);
	if (is_ray_facing_left(angl) && x_step > 0 || is_ray_facing_right(angl)
		&& x_step < 0)
		x_step *= -1;
	if (is_ray_facing_up(angl))
		inter_h.yintercept -= 0.0001;
	while (!find_wall(data, inter_h.xintercept, inter_h.yintercept))
	{
		inter_h.yintercept += y_step;
		inter_h.xintercept += x_step;
	}
	if (!data->ray->skip_door && get_door_inter(data, &inter_h, x_step, y_step))
		return (inter_h);
	return (inter_h);
}

t_inter	get_v_inter(t_data *data, float angl)
{
	t_inter	inter_v;
	double	x_step;
	double	y_step;

	inter_v.is_door = false;
	x_step = TILE_SIZE;
	start_v_x(data, angl, &inter_v.xintercept);
	inter_v.yintercept = data->ply->posY + (inter_v.xintercept
			- data->ply->posX) * tan(angl);
	if (is_ray_facing_left(angl))
		x_step *= -1;
	y_step = x_step * tan(angl);
	if (is_ray_facing_up(angl) && y_step > 0 || (is_ray_facing_down(angl)
			&& y_step < 0))
		y_step *= -1;
	if (is_ray_facing_left(angl))
		inter_v.xintercept -= 0.0001;
	while (!find_wall(data, inter_v.xintercept, inter_v.yintercept))
	{
		inter_v.xintercept += x_step;
		inter_v.yintercept += y_step;
	}
	return (inter_v);
}

void	raycasting(t_data *data)
{
	t_ray	*ray;
	double	angle;
	int		ray_x;
	double	angle_increment;

	ray_x = 0;
	ray = data->ray;
	angle = data->ply->angle - data->ply->fov_rd / 2;
	angle_increment = data->ply->fov_rd / S_W;
	while (ray_x < S_W)
	{
		data->ray->skip_door = 1;
		angle = normalize_angle(angle);
		ray->ray_ngl = angle;
		ray->distance = calculate_distance(data, angle);
		render_wall(data, ray_x, ray->ray_ngl);
		if (data->ray->hit_door || player_in_grid(data))
			cast_rays_door(data, ray_x);
		ray_x++;
		angle += angle_increment;
	}
}

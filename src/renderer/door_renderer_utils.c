/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:08:12 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/23 01:12:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

t_wall_door	*get_corret_door(t_data *data, t_wall_door **list_door)
{
	int		i;
	int		j;
	int		n;
	float	corr;

	corr = 0.001;
	if (is_ray_facing_up(data->ply->angle))
		corr *= -1;
	i = (int)(data->door->x_intercept / (double)TILE_SIZE + corr);
	j = (int)(data->door->y_intercept / (double)TILE_SIZE + corr);
	n = 0;
	while (n < 3 && list_door[n])
	{
		if (list_door[n]->i == i && list_door[n]->j == j)
			return (list_door[n]);
		n++;
	}
	return (NULL);
}

int	get_start_drawing_texture_x_door(t_door door_ray)
{
	int	offset;

	if (door_ray.is_ver_ray == 1)
		offset = (int)door_ray.x_intercept % TILE_SIZE;
	else
		offset = (int)door_ray.y_intercept % TILE_SIZE;
	return (offset);
}

t_texture	*selected_texture_door(t_data *data, t_ray ray)
{
	return (data->textures.door[data->door->current_frame]);
}

double	get_door_height(t_door *door, t_ray *ray, t_player ply)
{
	double	dis_player;
	double	wall_height;
	double	distance;

	dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);
	distance = door->distance * cos(ply.angle - ray->ray_ngl);
	wall_height = (dis_player * TILE_SIZE) / distance;
	return (wall_height);
}

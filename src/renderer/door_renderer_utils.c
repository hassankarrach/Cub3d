/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:08:12 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/20 21:08:19 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

t_wall_door	*get_corret_door(int i, int j, t_wall_door **list_door)
{
	int		n;

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
	int			i;
	int			j;
	t_wall_door	*c_door;

	i = (int)(ray.min_inter.xintercept / TILE_SIZE);
	j = (int)(ray.min_inter.yintercept / TILE_SIZE);
	c_door = get_corret_door(i, j, data->door->doors);
	data->door->current_frame = c_door->current_frame;
	return (data->textures.door[c_door->current_frame]);
}

double	get_door_height(t_door *door, t_ray *ray, t_player ply)
{
	double	dis_player;
	double	wall_height;
	double	distance;

	dis_player = (S_W / 2) / tan((ply.fov_rd) / 2);
	distance = door->distance * cos(ply.angle - ray->ray_ngl);
	wall_height = (dis_player * TILE_SIZE) / distance;
	return (wall_height);
}

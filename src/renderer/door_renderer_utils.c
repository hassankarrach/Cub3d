/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:08:12 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 05:08:13 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

// t_door *get_corret_door(t_door **list_door, x, y)
// {
//     int i;
//     int j;

//     i = (int)(x / (double)TILE_SIZE);
//     j = (int)(y / (double)TILE_SIZE);
//     while (list_door && list_door->next != NULL)
//     {
//         if (list_door->x == i && list_door->y == j)
//             break ;
//     }
//     return (*list_door);
// }

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
	double		dis_player;
	double		wall_height;
	double		distance;

	dis_player = (S_W / 2) / tan((FOV * DEG_TO_RAD) / 2);
	distance = door->distance * cos(ply.angle - ray->ray_ngl);
	wall_height = (dis_player * TILE_SIZE) / distance;
	return (wall_height);
}

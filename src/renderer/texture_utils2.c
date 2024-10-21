/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 04:17:02 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 04:17:03 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

t_texture	*get_vertical_texture(t_data *data, float ray_angle)
{
	if (is_ray_facing_up(ray_angle))
	{
		if (check_wall_frame(*data))
			return (get_wall_frame(*data, TOP, data->textures.wall_NO));
		return (data->textures.wall_NO);
	}
	else if (is_ray_facing_down(ray_angle))
	{
		if (check_wall_frame(*data))
			return (get_wall_frame(*data, BOTTOM, data->textures.wall_SO));
		return (data->textures.wall_SO);
	}
	return (NULL);
}

t_texture	*get_horizontal_texture(t_data *data, float ray_angle)
{
	if (is_ray_facing_left(ray_angle))
	{
		if (check_wall_frame(*data))
			return (get_wall_frame(*data, LEFT, data->textures.wall_WE));
		return (data->textures.wall_WE);
	}
	else if (is_ray_facing_right(ray_angle))
	{
		if (check_wall_frame(*data))
			return (get_wall_frame(*data, RIGHT, data->textures.wall_EA));
		return (data->textures.wall_EA);
	}
	return (NULL);
}

t_texture	*selected_texture(t_data *data, t_ray ray, float ray_angle)
{
	if (ray.v_or_h == 1)
		return (get_vertical_texture(data, ray_angle));
	else
		return (get_horizontal_texture(data, ray_angle));
}

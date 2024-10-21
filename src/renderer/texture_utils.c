/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 04:26:31 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 04:37:27 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

int	get_pixel(t_texture *texture, int offset_x, int offset_y)
{
	int	pixel_offset;
	int	color;

	if (texture == NULL)
		return (0);
	if (offset_x < 0 || offset_x >= texture->width || offset_y < 0
		|| offset_y >= texture->height)
		return (0);
	pixel_offset = (offset_y * texture->line_length) + (offset_x
			* (texture->bits_per_pixel / 8));
	color = *(int *)(texture->addr + pixel_offset);
	return (color);
}

int	get_start_drawing_texture_x(t_ray ray)
{
	int	offset;

	if (ray.v_or_h == 1)
		offset = (int)ray.min_inter.xintercept % TILE_SIZE;
	else
		offset = (int)ray.min_inter.yintercept % TILE_SIZE;
	return (offset);
}

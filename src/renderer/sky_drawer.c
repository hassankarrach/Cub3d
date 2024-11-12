/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_drawer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:54:04 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/12 02:42:08 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

double	calculate_normalized_distance(int x, int y, t_sky_params *params)
{
	double	distance;

	distance = 0;
	distance = sqrt((x - params->center_x) * (x - params->center_x)
			+ (y - params->center_y_sky) * (y - params->center_y_sky));
	if (distance / params->max_distance > 1.0)
		return (1.0);
	return (distance / params->max_distance);
}

int	calculate_sky_color(double normalized_distance)
{
	double	bright_factor;
	int		r;
	int		g;
	int		b;

	if (normalized_distance > 1.0)
		normalized_distance = 1.0;
	if (normalized_distance < 0.0)
		normalized_distance = 0.0;
	bright_factor = pow(normalized_distance, 3);
	r = (int)(bright_factor * 1);
	r = clamp(r, 0, 255);
	g = (int)(bright_factor * 32);
	g = clamp(g, 0, 255);
	b = (int)(bright_factor * 71);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

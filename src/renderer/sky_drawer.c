/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_drawer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:54:04 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 22:55:09 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

double	calculate_normalized_distance(int x, int y, t_sky_params *params)
{
	double	distance;

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

	bright_factor = pow(normalized_distance, 3);
	r = (int)((1.0 - bright_factor) * 0 + bright_factor * 1);
	g = (int)((1.0 - bright_factor) * 0 + bright_factor * 32);
	b = (int)((1.0 - bright_factor) * 0 + bright_factor * 71);
	return ((r << 16) | (g << 8) | b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:33:11 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/21 03:33:12 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

int	is_ray_facing_down(float rayAngle)
{
	return (rayAngle > 0 && rayAngle < M_PI);
}

int	is_ray_facing_up(float rayAngle)
{
	return (!is_ray_facing_down(rayAngle));
}

int	is_ray_facing_right(float rayAngle)
{
	return (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
}

int	is_ray_facing_left(float rayAngle)
{
	return (!is_ray_facing_right(rayAngle));
}

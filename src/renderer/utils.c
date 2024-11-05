/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:05:21 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/05 23:03:06 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x
			* (data->mlx->bits_per_pixel / 8));
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		*(int *)dst = color;
}

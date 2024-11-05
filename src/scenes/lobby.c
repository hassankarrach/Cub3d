/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:04:25 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 23:04:43 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scenes.h"

void	lobby(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->win, data->textures.logo->img, 250, 200);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->textures.press_to_start->img, 250, (S_H - 150));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:04:25 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/23 09:51:55 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scenes.h"

void	lobby(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->textures.press_to_start->img, 0, 0);
}

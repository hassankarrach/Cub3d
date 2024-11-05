/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:03:57 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 23:04:51 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scenes.h"

void	game_pause(t_data *data)
{
	mlx_string_put(data->mlx->mlx, data->mlx->win, S_W
		/ 2 - 50, S_H / 2, 0x00FFFFFF, "PAUSED");
}

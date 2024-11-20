/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:23:23 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/20 21:15:56 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static bool	hit_wall(t_data *data, double x, double y)
{
	int			i;
	int			j;

	i = (int)(x / (double)TILE_SIZE);
	j = (int)(y / (double)TILE_SIZE);
	if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
		return (1);
	else if (data->map2d[j][i] == '1' || data->map2d[j][i] == 'F')
		return (1);
	return (0);
}

static int	valid_move2(t_data *data, double x, double y)
{
	if (hit_wall(data, x + 25, y - 25))
		return (1);
	else if (hit_wall(data, x - 25, y + 25))
		return (1);
	else if (hit_wall(data, x - 25, y - 25))
		return (1);
	else if (hit_wall(data, x + 25, y + 25))
		return (1);
	return (0);
}

static int	valid_move(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = (int)(x / (double)TILE_SIZE);
	j = (int)(y / (double)TILE_SIZE);
	if (i >= data->w_map || j >= data->h_map || i < 0 || j < 0)
		return (1);
	else if (data->map2d[j][i] == 'O')
	{
		data->ply->move_speed = 1;
		data->ply->bobbing_speed = 1;
		data->ply->bobbing_amplitude = 1;
	}
	else if (valid_move2(data, x, y))
		return (1);
	return (0);
}

void	head_bobbing(t_data *data)
{
	static double	bobbing_time = 0;

	if (data->ply->walk_direction)
	{
		bobbing_time += BOBBING_SPEED * data->ply->bobbing_speed;
		data->ply->look_offset += sin(bobbing_time) * BOBBING_AMPLITUDE
			* data->ply->bobbing_amplitude;
	}
}

void	update_player(t_player *player, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x;
	new_y = player->pos_y;
	player->angle += player->turn_direction * ROTATION_SPEED;
	player->angle = normalize_angle(player->angle);
	new_x += player->walk_direction * (MOVE_SPEED * data->ply->move_speed)
		* cos(player->angle);
	new_y += player->walk_direction * (MOVE_SPEED * data->ply->move_speed)
		* sin(player->angle);
	if (!valid_move(data, new_x, player->pos_y))
	{
		player->pos_x = new_x;
	}
	if (!valid_move(data, player->pos_x, new_y))
	{
		player->pos_y = new_y;
	}
	head_bobbing(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:01:14 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/12 02:53:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_player *player, t_data *data)
{
	get_x_y_player(data);
	player->pos_x = data->index_x * TILE_SIZE + TILE_SIZE / 2;
	player->pos_y = data->index_y * TILE_SIZE + TILE_SIZE / 2;
	player->fov_rd = 60 * (M_PI / 180);
	player->look_offset = 0;
	player->walk_direction = 0;
	player->turn_direction = 0;
	data->ply->move_speed = 1;
	data->ply->bobbing_speed = 1;
	data->ply->bobbing_amplitude = 1;
	data->last_update_time = get_time_in_seconds();
	get_angle(data);
	init_player_texture(data, data->ply, data->textures.player);
}

void	get_angle(t_data *m)
{
	if (m->ply->player_dir == 'N')
		m->ply->angle = 3 * M_PI / 2;
	else if (m->ply->player_dir == 'S')
		m->ply->angle = M_PI / 2;
	else if (m->ply->player_dir == 'W')
		m->ply->angle = M_PI;
	else if (m->ply->player_dir == 'E')
		m->ply->angle = 0;
}

void	get_x_y_player(t_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->args->map_lines[i])
	{
		j = 0;
		while (m->args->map_lines[i][j])
		{
			if (m->args->map_lines[i][j] == 'N'
				|| m->args->map_lines[i][j] == 'S'
				|| m->args->map_lines[i][j] == 'W'
				|| m->args->map_lines[i][j] == 'E')
			{
				m->ply->player_dir = m->args->map_lines[i][j];
				m->index_x = j;
				m->index_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

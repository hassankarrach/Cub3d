/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:01:14 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/22 01:34:13 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

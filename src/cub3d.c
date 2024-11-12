/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:56:01 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/12 03:11:19 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	game_logic(t_data *data, double time_between_frames)
{
	double			current_time;
	static double	bobbing_time = 0;

	mlx_clear_window(data->mlx->mlx, data->mlx->win);
	current_time = get_time_in_seconds();
	if (!data->ply->walk_direction)
	{
		if (current_time - data->last_update_time >= time_between_frames)
		{
			bobbing_time += 0.08;
			data->ply->look_offset += sin(bobbing_time) * 3;
			data->last_update_time = current_time;
		}
	}
	draw_sky_floor(data);
	drawer_floor(data, 0);
	raycasting(data);
	render_mini_map(data);
	update_door_status(data, current_time);
	update_ply_animation(data, data->ply, current_time);
	update_player(data->ply, data);
	draw_player(data, current_time);
	drawing_3d_game(data);
}

static int	game_loop(void *arg)
{
	double			time_between_frames;
	t_data			*data;

	time_between_frames = 0.03;
	data = (t_data *)arg;
	if (data->state == LOBBY)
		lobby(data);
	else if (data->state == PAUSED)
		game_pause(data);
	else
		game_logic(data, time_between_frames);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	cub3d_args;
	t_data	data;

	parser(ac, av, &cub3d_args);
	init_game(&data, &cub3d_args);
	handle_events(&data);
	mlx_loop_hook(data.mlx->mlx, game_loop, &data);
	mlx_loop(data.mlx->mlx);
	return (0);
}

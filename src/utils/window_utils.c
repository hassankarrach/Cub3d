/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:19:14 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/20 20:42:27 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	handle_events(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == ON_KEYUP)
		data->ply->walk_direction = 1;
	if (keycode == KEY_S)
		data->ply->walk_direction = -1;
	if (keycode == KEY_A)
		data->ply->turn_direction = -1;
	if (keycode == KEY_D)
		data->ply->turn_direction = 1;
	if (keycode == ON_KEYUP)
	{
		data->ply->move_speed = 3;
		data->ply->bobbing_speed = 1.9;
		data->ply->bobbing_amplitude = 1.4;
	}
	if (keycode == 112)
		data->state = PAUSED;
	if (keycode == 32)
		data->state = PLAYING;
	if (keycode == KEY_VOLUMEDOWN && data->increase > 20)
		data->increase -= 4;
	if (keycode == KEY_VOLUMEUP && data->increase < 40)
		data->increase += 4;
	if (keycode == ON_DESTROY)
		close_window(data);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x = 0;
	static int	last_y = S_W / 2;
	int			mouse_delta_x;
	int			mouse_delta_y;

	mouse_delta_x = x - last_x;
	mouse_delta_y = y - last_y;
	last_x = x;
	last_y = y;
	if (data->flag != 0)
		data->ply->angle += mouse_delta_x * (ROTATION_SPEED * 0.03);
	data->ply->angle = normalize_angle(data->ply->angle);
	data->ply->look_offset -= mouse_delta_y * 2;
	data->flag = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == ON_KEYUP)
		data->ply->walk_direction = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		data->ply->turn_direction = 0;
	if (keycode == ON_KEYUP)
	{
		data->ply->move_speed = 1;
		data->ply->bobbing_speed = 1;
		data->ply->bobbing_amplitude = 1;
	}
	return (0);
}

int	close_window(t_data *data)
{
	clean_resources(data);
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:59:01 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/08 20:59:37 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../includes/cub3d.h"

typedef struct s_texture	t_texture;

enum
{
	ON_KEYDOWN = 65364,
	ON_KEYUP = 65362,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 65307,
	ON_TURN_LEFT = 65361,
	ON_TURN_RIGHT = 65363,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFTSHIFT = 65505,
	KEY_VOLUMEDOWN = 65453,
	KEY_VOLUMEUP = 65451
};

typedef struct s_player
{
	double					angle;
	double					fov_rd;
	char					player_dir;
	double					pos_x;
	double					pos_y;
	int						look_offset;
	int						walk_direction;
	int						turn_direction;
	int						move_speed;
	double					bobbing_speed;
	double					bobbing_amplitude;
	double					last_update_time;
	int						current_frame;
	int						total_frames;
}							t_player;

#endif
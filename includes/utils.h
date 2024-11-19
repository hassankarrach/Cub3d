/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:18:20 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/19 03:34:30 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_coord
{
	int	map_x;
	int	map_y;
}	t_coord;

typedef struct s_data	t_data;
typedef struct s_args	t_args;
typedef struct s_mlx	t_mlx;
typedef struct s_texture	t_texture;

int						ft_error(t_args *args, char *error_msg,
							bool should_exit,
							bool should_free);
void					render_mini_map(t_data *data);
void					head_bobbing(t_data *data);
void					update_player(t_player *player, t_data *data);
void					handle_events(t_data *data);
int						key_press(int keycode, t_data *data);
int						mouse_move(int x, int y, t_data *data);
int						key_release(int keycode, t_data *data);
int						close_window(t_data *data);
double					get_time_in_seconds(void);
int						clamp(int value, int min, int max);
void					ft_pixel_put(t_data *data, int x, int y, int color);
void					clean_resources(t_data *data);
int						pos_to_color(t_data *data, int x, int y);
void					freer(t_args *args);
void					helper_clean(t_data *data);
void					free_texture(t_mlx *mlx, t_texture *texture);
void					free_mlx(t_mlx *ptr);
int						adjust_color_opacity2(int color, float fade_factor);

#endif
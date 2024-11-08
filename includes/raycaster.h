/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:16:49 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/08 21:17:25 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../includes/cub3d.h"
# include "../includes/player.h"

typedef struct s_data	t_data;
typedef struct s_ray	t_ray;

typedef struct s_inter
{
	bool				is_door;
	double				xintercept;
	double				yintercept;
}						t_inter;
typedef struct s_ray
{
	double				ray_ngl;
	bool				skip_door;
	double				distance;
	int					v_or_h;
	double				wall_height;
	bool				hit_door;
	t_inter				min_inter;
}						t_ray;

double					normalize_angle(double angle);
double					ft_distance(t_data *data, double x, double y);
double					calculate_distance(t_data *data, float angle);
void					start_h_y(t_data *data, double angl, double *h_y);
void					start_v_x(t_data *data, double angl, double *v_x);
void					start_h_y_door(t_data *data, double angl, double *h_y);
int						find_wall(t_data *data, double x, double y);
bool					is_door(double x, double y, t_data *data);
bool					player_in_grid(t_data *data);
bool					get_door_inter_h(t_data *data, t_inter *inter_h,
							double x_step, double y_step);
void					cast_rays_door(t_data *data, int ray);
bool					is_within_map(double x, double y, t_data *data);
bool					is_door_2(double x, double y, t_data *data);
t_inter					min_distance(t_inter inter_h, t_inter inter_v,
							t_data *data);

#endif

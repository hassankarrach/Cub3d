#ifndef RENDERER_H
# define RENDERER_H

# include "cub3d.h"

typedef struct s_data			t_data;
typedef struct s_texture		t_texture;
typedef struct s_wall_params	t_wall_params;
typedef struct s_ray			t_ray;
typedef enum Direction e_Direction;
typedef struct s_door t_door;
typedef struct s_wall_door t_wall_door;

void							draw_sky_floor(t_data *data);
t_texture						*texture_loader(t_data *data,
									char *texture_path);
int								get_pixel(t_texture *texture,
									int offset_x, int offset_y);
int								get_start_drawing_texture_x(t_ray ray);
t_wall_params					calculate_wall_params(t_data *data);
void							render_wall(t_data *data, int x, double angle);
void							drawing_3d_game(t_data *data);
void							draw_player(t_data *data, double current_time);
t_texture						*selected_texture(t_data *data, t_ray ray,
									float ray_angle);
int								get_pixel(t_texture *texture,
									int offset_x, int offset_y);
int								get_start_drawing_texture_x(t_ray ray);
int								check_wall_frame(t_data data);
t_texture                       *get_wall_frame(t_data data, e_Direction direction,
                                t_texture *texture_wall);
int								get_start_drawing_texture_x_door(t_door door_ray);
t_texture						*selected_texture_door(t_data *data, t_ray ray);
double							get_door_height(t_door *door, t_ray *ray, t_player ply);
t_wall_door						*get_corret_door(int i, int j, t_wall_door **list_door);

#endif
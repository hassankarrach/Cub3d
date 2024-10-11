#ifndef RENDERER_H
#define RENDERER_H

#include "cub3d.h"

typedef struct s_data t_data;
typedef struct s_texture t_texture;
typedef struct s_wall_params t_wall_params;
typedef struct s_ray t_ray;

void draw_sky_floor(t_data *data);
t_texture *texture_loader(t_data *data, char *texture_path);
int get_pixel_from_texture(t_texture *texture, int offset_x, int offset_y);
int get_start_drawing_texture_x(t_ray ray);
t_wall_params calculate_wall_params(t_data *data);
void render_wall(t_data *data, int x);
void drawing_3d_game(t_data *data);


#endif
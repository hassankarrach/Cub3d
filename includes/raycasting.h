#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../includes/cub3d.h"
#include "../includes/player.h"

typedef struct s_inter {
    bool is_door;
    double xintercept;
    double yintercept;
    double x_intercept_door;
    double y_intercept_door;
} t_inter;
typedef struct s_ray {
    double ray_ngl;
    bool skip_door;
    double distance;
    int v_or_h;
    double wall_height;
    bool hit_door;
    t_inter min_inter;
} t_ray;

#endif
#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../includes/cub3d.h"
#include "../includes/player.h"

typedef struct s_ray {
    double ray_ngl;  // the start angle
    double distance; // the distance to the wall
    double angleIncrement; // the angle increment
    int v_or_h;
} t_ray;

#endif
#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../includes/cub3d.h"
#include "../includes/player.h"

typedef struct s_ray {
    double ray_ngl;  // the start angle
    double distance; // the distance to the wall
    float h_distance;
    float v_distance;
    double angleIncrement; // the angle increment
    int v_or_h;
    double h_x;
    double v_y;
    float floorX;
    float floorY;
    double wall_height;
    int hit_door;
    float xintercept_h;
    float yintercept_h;
    float xintercept_v;
    float yintercept_v;
    int front_x;
    int front_y;
} t_ray;
#endif
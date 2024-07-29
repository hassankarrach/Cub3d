#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../includes/cub3d.h"
#include "../includes/player.h"

//Ray Structure
typedef struct s_ray {
    double ray_ngl;  // the start angle
    double distance; // the distance to the wall
    double angleIncrement; // the angle increment
} t_ray;    

//Main Game Structure
typedef struct s_game {
    t_player player;
    int screenWidth;
    int screenHeight;
    // Add other necessary components like textures, buffers, etc.
} t_game;



#endif
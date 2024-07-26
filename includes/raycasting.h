#ifndef RAYCASTING_H
#define RAYCASTING_H

//Player Structure
typedef struct s_player {
    double angle;
    double fov_rd;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_player;

//Ray Structure
typedef struct s_ray {
    double ray_ngl;  // the start angle
    double distance; // the distance to the wall
    double angleIncrement; // the angle increment
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX; // the current map square
    int mapY;   // the current map square
    double sideDistX; // the distance to the next x or y side
    double sideDistY; // the distance to the next x or y side
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int hit;
    int side;
} t_ray;

//Main Game Structure
typedef struct s_game {
    t_player player;
    int screenWidth;
    int screenHeight;
    // Add other necessary components like textures, buffers, etc.
} t_game;



#endif
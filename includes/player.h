#ifndef PLAYER_H
#define PLAYER_H

#include "../includes/cub3d.h"

enum {
    ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
    ON_MOVE_LEFT = 0,
    ON_MOVE_RIGHT = 1,
    ON_TURN_LEFT = 2,
    ON_TURN_RIGHT = 3
};

//Player Structure
typedef struct s_player {
    double angle; // the player angle
    double fov_rd; // the field of view in radians
    double posX; // the player position
    double posY;
    double dirX; // the player direction
    double dirY; 
    double planeX; // the 2d raycaster version of camera plane
    double planeY;
    float move_up; // the player movement
    float move_down;
    float move_left;
    float move_right;
    float turn_left; // the player rotation
    float turn_right;
} t_player;

#endif
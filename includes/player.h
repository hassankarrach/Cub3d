#ifndef PLAYER_H
#define PLAYER_H

#include "../includes/cub3d.h"

enum {
    ON_KEYDOWN = 65364,
	ON_KEYUP = 65362,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 65307,
    ON_TURN_LEFT = 65361,
    ON_TURN_RIGHT = 65363
};

//Player Structure
typedef struct s_player {
    double angle; // the player angle
    double fov_rd; // the field of view in radians
    char player_dir;
    double posX; // the player position
    double posY;
    int walk_direction; // the player walk direction
    int turn_direction; // the player turn direction
} t_player;

#endif
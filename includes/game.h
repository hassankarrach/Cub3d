#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <unistd.h>
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <signal.h>
#include "cub3d.h"
//Sound
// #include <mpg123.h>
// #include <ao/ao.h>

typedef struct s_data t_data;
typedef struct s_sound t_sound;

#define LOBBY_SOUND_PATH "assets/sounds/lobby.wav"
#define AMBIENCE_SOUND_PATH "assets/sounds/ambience.wav"
#define PSST_SOUND_PATH "assets/sounds/Psst.wav"
#define WALKING_SOUND_PATH "assets/sounds/walking.wav"
#define YOU_DEAD_SOUND_PATH "assets/sounds/you_dead.wav"

// sounds_utils


// game
void lobby(t_data *data);
void you_died(t_data *data);
void game_pause(t_data *data);

#endif

// game logic

// 1 - each 10s, a Psst image should be displayed somewhere on the map arround the player.
// 2 - the player should find it and look on it to make it disappear.
// 3 - once he look on it, a black horror screen should appear.
// 4 - if a player failed to look on it within 5s, a you died screen should appear.
// 5 - and so on...

#ifndef SCENES_H
#define SCENES_H

#include <stdlib.h>
#include <unistd.h>
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <signal.h>
#include "cub3d.h"


typedef struct s_data t_data;
typedef struct s_sound t_sound;

#define LOBBY_SOUND_PATH "assets/sounds/lobby.wav"
#define AMBIENCE_SOUND_PATH "assets/sounds/ambience.wav"
#define PSST_SOUND_PATH "assets/sounds/Psst.wav"
#define WALKING_SOUND_PATH "assets/sounds/walking.wav"
#define YOU_DEAD_SOUND_PATH "assets/sounds/you_dead.wav"

void lobby(t_data *data);
void you_died(t_data *data);
void game_pause(t_data *data);

#endif


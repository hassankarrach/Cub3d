#ifndef UTILS_H
#define UTILS_H

#include "cub3d.h"

typedef struct s_data t_data;

int ft_error(char *error_msg);
void render_mini_map(t_data *data);
void Head_Bobbing(t_data *data);
void update_player(t_player *player, t_data *data);
void handle_events(t_data *data);
int key_press(int keycode, t_data *data);
int mouse_move(int x, int y, t_data *data);
int key_release(int keycode, t_data *data);
int close_window(t_data *data);
double get_time_in_seconds(void);
int	clamp(int value, int min, int max);

#endif
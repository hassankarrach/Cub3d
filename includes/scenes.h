#ifndef SCENES_H
# define SCENES_H

# include "../lib/libft/libft.h"
# include "cub3d.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data	t_data;

void					lobby(t_data *data);
void					game_pause(t_data *data);

#endif

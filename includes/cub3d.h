// main header
#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>

// libs includes
#include "../lib/libft/libft.h"

// Macros  =>
# define S_W 1900 // screen width
# define S_H 1000 // screen height
// ==========


// Structs =>
typedef struct s_player{
	int player_x;
	int player_y;
} t_player;
// ==========


// ERRORs - CLEANUPs
int		ft_error(char *error_msg);

// PARSING
void    parser(int ac, char **av);


#endif
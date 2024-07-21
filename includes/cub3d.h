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
typedef struct s_rgb{
	int r;
	int g;
	int b;
}	t_rgb;

typedef	struct s_args{
	t_rgb	Floor_color;
	t_rgb	Ceiling_color;
	char	*North_texture;
	char	*South_texture;
	char	*West_texture;
	char	*East_texture;
	char	**map_lines;
}	t_args;
// ==========


// ERRORs - CLEANUPs
int		ft_error(char *error_msg);

// PARSING
void    parser(int ac, char **av, t_args *cub3d_args);
char	*texture_path_extracter(char *line);
void    rgb_extracter(char *line, t_args *cub3d_args, char flag);


#endif
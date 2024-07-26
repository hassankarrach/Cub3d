// main header
#ifndef CUB3D_H
#define CUB3D_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

// libs includes ================>
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
#include "../lib/raycasting.h"
// ===============================

// Macros  ======================>
#define S_W 1900 // screen width
#define S_H 1000 // screen height
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
#define DEG_TO_RAD (M_PI / 180.0)

# define BLK 0x000000FF
# define GREY 0x808080FF
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFFFFF

// ===============================

// Structs ======================>
typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_args
{
	t_rgb Floor_color;
	t_rgb Ceiling_color;
	char *North_texture;
	char *South_texture;
	char *West_texture;
	char *East_texture;
	char **map_lines;
} t_args;

typedef struct s_data
{
	char	**map2d;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
	t_args *args;
	t_mlx	*mlx;
	t_tex	*tex;
	t_ray	*ray;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_data	*data;
}	t_mlx;
// ===============================

// ERRORs - CLEANUPs
int ft_error(char *error_msg);

// PARSING
void parser(int ac, char **av, t_args *cub3d_args);
void texture_path_extracter(char *line, char **to_be_filled);
void rgb_extracter(char *line, t_rgb *rgb);

#endif
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
#include "raycasting.h"
// #include "../includes/parser.h"
#include "player.h"
// ===============================

// Macros  ======================>
#define S_W 1200 // screen width
#define S_H 600 // screen height
#define S_W_MINI_MAP 20
#define S_H_MINI_MAP 15
#define S_TITLE "Cub3D"
# define TILE_SIZE 32
#define M_PI 3.14159265358979323846
# define FOV 60
# define ROTATION_SPEED 0.005
# define MOVE_SPEED 4
# define PLAYER_SPEED 4
#define DEG_TO_RAD (M_PI / 180)

# define BLK 0x000000FF
# define GREY 0x808080FF
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFFFFF

// ===============================

// Structs ======================>
typedef struct s_mlx t_mlx;
typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

// typedef struct s_tex
// {
// 	mlx_texture_t	*no;
// 	mlx_texture_t	*so;
// 	mlx_texture_t	*we;
// 	mlx_texture_t	*ea;
// }	t_tex;

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
	int		w_map;
	int		h_map;
	t_args *args;
	t_mlx	*mlx;
	// t_tex	*tex;
	t_ray	*ray;
	t_player *ply;
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

// GAME
void init_game(t_data *data, t_args *args);
void render_mini_map(t_data *data, char **map);
void handle_events(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int close_window(t_data *data);
void raycasting(t_data *data);
void	get_x_y_player(t_data *m);
float get_h_inter(t_data *data, float angl);
float get_v_inter(t_data *data, float angl);
double normalize_angle(double angle);
float calculate_distance(t_data *data, float angle);
void start_h_y(t_data *data, float angl, float *h_y);
void start_v_x(t_data *data, float angl, float *v_x);
void get_angle(t_data *m);
void update_player(t_player *player);
void draw_minimap(void *mlx, void *win, t_data *data);

#endif
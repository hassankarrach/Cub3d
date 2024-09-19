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
#include <stdbool.h>

// libs includes ================>
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
#include "raycasting.h"
// #include "../includes/parser.h"
#include "player.h"
#include "game.h"
// ===============================

// Macros  ======================>
#define S_W 1000 // screen width
#define S_H 1000 // screen height
// #define S_W 640 // screen width
// #define S_H 256 // screen height
#define S_W_MINI_MAP 20
#define S_H_MINI_MAP 15
#define S_TITLE "Cub3D"
#define TILE_SIZE 576
#define M_PI 3.14159265358979323846
# define FOV 60
# define ROTATION_SPEED 0.10
# define MOVE_SPEED 6
#define BOBBING_SPEED 0.4
#define BOBBING_AMPLITUDE 4
#define DEG_TO_RAD (M_PI / 180)

#define BLK 0xFF000000	// Black
#define GREY 0xFF808080 // Grey
#define BLU 0xFF87CEEB	// Light Blue
#define GREN 0xFF008000 // Green
#define ORNG 0xFFFF9300 // Orange
#define RED 0xFFFF0000	// Red
#define WHI 0xFFFFFFFF	// White
#define MOR_BLU 0xFF000033

// ===============================

// Structs ======================>
typedef struct s_mlx t_mlx;
typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;
typedef struct s_sound
{
	const char *file_path;
	pid_t pid;
	int is_playing;
} t_sound;
typedef struct s_texture
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_texture;

typedef enum e_game_state
{
	LOBBY,
	PLAYING,
	PAUSED,
	DEAD
} game_state;

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
	char **map2d;
	int index_x;
	int index_y;
	int w_map;
	int h_map;
	t_args *args;
	t_mlx *mlx;
	t_texture *texture1;
	t_texture *texture2;
	t_texture *player[14];
	t_texture *logo;
	t_texture *press_to_start;
	t_texture *you_died;
	// t_tex	*tex;
	t_ray *ray;
	t_player *ply;

	t_sound sounds[5];

	game_state state;
} t_data;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_data *data;
} t_mlx;
// ===============================

// ERRORs - CLEANUPs
int ft_error(char *error_msg);

// PARSING
void parser(int ac, char **av, t_args *cub3d_args);
void texture_path_extracter(char *line, char **to_be_filled);
void rgb_extracter(char *line, t_rgb *rgb);

// GAME
void init_game(t_data *data, t_args *args);
void render_mini_map(t_data *data);
void handle_events(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int close_window(t_data *data);
void raycasting(t_data *data);
void get_x_y_player(t_data *m);
float get_h_inter(t_data *data, float angl);
float get_v_inter(t_data *data, float angl);
double normalize_angle(double angle);
float calculate_distance(t_data *data, float angle);
void start_h_y(t_data *data, float angl, float *h_y);
void start_v_x(t_data *data, float angl, float *v_x);
void get_angle(t_data *m);
void update_player(t_player *player, t_data *data);
void draw_minimap(void *mlx, void *win, t_data *data);
void draw_2d_game(t_data *data);
void draw_line(t_data *data, int x0, int y0, int x1, int y1);
int find_wall(t_data *data, double x, double y);
int isRayFacingDown(float rayAngle);
int isRayFacingUp(float rayAngle);
int isRayFacingRight(float rayAngle);
int isRayFacingLeft(float rayAngle);
void ft_pixel_put(t_data *data, int x, int y, int color);
void draw_sky_floor(t_data *data);
void render_wall(t_data *data, double distance, int x, double ray_angl);
void drawing_3d_game(t_data *data);
t_texture *texture_loader(t_data *data, char *texture_path);
void set_floor_coords(t_data *data, int ray);
void floor_casting(t_data *data, int x);
int get_pixel_from_texture(t_texture *texture, int offset_x, int offset_y);
t_texture *png_texture_loader(t_data *data, char *texture_path);
int mouse_move(int x, int y, t_data *data);
int mouse_release(int button, int x, int y, t_data *data);

#endif
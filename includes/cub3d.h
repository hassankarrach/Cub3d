// main header
#ifndef CUB3D_H
#define CUB3D_H

//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>

// libs includes ================>
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
// ===============================

// inner includes ===============>
#include "parser.h"
#include "player.h"
#include "scenes.h"
#include "raycaster.h"
#include "renderer.h"
#include "utils.h"
// ===============================

// Macros  ======================>
#define S_W 1000 // screen width
#define S_H 1000 // screen height
// #define S_W 640 // screen width
// #define S_H 256 // screen height
#define S_W_MINI_MAP 286
#define S_H_MINI_MAP 215
#define S_TITLE "Cub3D"
#define TILE_SIZE 576
#define M_PI 3.14159265358979323846
#define FOV 60
#define ROTATION_SPEED 4 * DEG_TO_RAD //  2 * (PI / 180)
#define MOVE_SPEED 7
#define BOBBING_SPEED 0.3
#define BOBBING_AMPLITUDE 3
#define DEG_TO_RAD (M_PI / 180)

#define BLK 0xFF000000	// Black
#define GREY 0xFF808080 // Grey
#define BLU 0xFF87CEEB	// Light Blue
#define GREN 0xFF008000 // Green
#define ORNG 0xFFFF9300 // Orange
#define RED 0xFFFF0000	// Red
#define WHI 0xFFFFFFFF	// White
#define MOR_BLU 0xFF000033
#define MAP_CLR 0xBA7728

// ===============================

// Structs ======================>
typedef struct s_mlx t_mlx;
typedef struct s_vec t_vec;
typedef struct s_inter t_inter;

typedef enum FrameType e_FrameType;
typedef enum Direction e_Direction;
typedef struct s_wallFrame t_wallFrame;

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

typedef struct s_args
{
    t_rgb Floor_color;
    t_rgb Ceiling_color;
    char *North_texture;
    char *South_texture;
    char *West_texture;
    char *East_texture;
    char **map_lines;
    int map_rows;
    int map_columns;
    int number_of_frames;
    t_wallFrame **frames;
} t_args;

typedef struct s_door
{
	double distance;
	bool is_ver_ray;
	bool is_open;
	int current_frame;
	int total_frames;		 // Total frames for the door animation (e.g., 8)
	double x_intercept;		 // X intersection for the door
	double y_intercept;		 // Y intersection for the door
	double last_update_time; // Last time the frame was updated
	t_texture *textures[8];	 // Textures for each animation frame (8 in this case)
} t_door;

typedef struct s_texture_frame_13
{
	t_texture *frame_red;
	t_texture *frame_green;
	t_texture *frame_blue;
	t_texture *frame_orange;
} t_frames;


typedef struct s_textures
{
	t_texture *wall_SO;
	t_texture *wall_WE;
	t_texture *wall_EA;
	t_texture *wall_NO;

	t_texture *wall_frame1;
	t_texture *wall_frame2;

	t_texture *player[26];
	t_texture *door[24];

	t_texture *logo;
	t_texture *press_to_start;
	t_texture *you_died;
	t_texture *mini_map;
	t_texture *icon_player;
	t_frames frame_13;
	t_frames frame_doors;
} t_textures;

typedef struct s_data
{
	char **map2d;
	int index_x;
	int index_y;
	int w_map;
	int h_map;
	t_args *args;
	t_mlx *mlx;
	t_mlx *mlx_map;
	
	//textures ========
	t_textures textures;
	//=================

	t_door *door;
	t_ray *ray;
	t_player *ply;
	t_sound sounds[5];
	game_state state;
	int flag;
	int selected_wall;
	int increase;
} t_data;

typedef struct s_wall_params
{
	int start_y;
	int end_y;
	int save_y;
	int texture_x;
	int texture_y;
	double wall_height;
	double brightness_factor;
} t_wall_params;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	void *img_map;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_data *data;
} t_mlx;

// ===============================
// GAME
void init_game(t_data *data, t_args *args);
void raycasting(t_data *data);
void get_x_y_player(t_data *m);
t_inter get_h_inter(t_data *data, float angl);
t_inter get_v_inter(t_data *data, float angl);
void get_angle(t_data *m);
int find_wall(t_data *data, double x, double y);
int is_ray_facing_down(float rayAngle);
int is_ray_facing_up(float rayAngle);
int is_ray_facing_right(float rayAngle);
int is_ray_facing_left(float rayAngle);
void load_door_textures(t_data *data);
void rendring_door(t_data *data, t_door door, int x);
void update_door_animation(t_data *data, t_door *door, double current_time);
void update_ply_animation(t_data *data, t_player *ply, double current_time);
bool player_in_grid(t_data *data);

#endif
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
# include <sys/time.h>

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
#define S_W_MINI_MAP 286
#define S_H_MINI_MAP 215
#define S_TITLE "Cub3D"
#define TILE_SIZE 576
#define M_PI 3.14159265358979323846
# define FOV 60
# define ROTATION_SPEED 4 * DEG_TO_RAD //  2 * (PI / 180) 
# define MOVE_SPEED 7
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
#define MAP_CLR 0xBA7728

// ===============================

// Structs ======================>
typedef struct s_mlx t_mlx;
typedef struct	s_vec t_vec;
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
typedef struct s_sprite
{
    double x, y;  // Sprite position in the game world
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			height;
	int			draw_start_y;
	int			draw_end_y;
	int			width;
	int			draw_start_x;
	int			draw_end_x;
	double scale;
    t_texture *texture;  // Pointer to the sprite texture
    double distance;  // Distance from the player (for sorting)
} t_sprite;
typedef struct s_door
{
	double distance;
	bool is_ver_ray;
    bool is_open;         // Flag to indicate if the door is open (1: open, 0: closed)
	bool is_close;
	bool is_near;
    int         current_frame;   // Current frame for the door animation
    int         total_frames;    // Total frames for the door animation (e.g., 8)
    double      x_intercept;     // X intersection for the door
    double      y_intercept;     // Y intersection for the door
	t_inter     *inter_v;
	t_inter		*inter_h;
    double      last_update_time; // Last time the frame was updated
    t_texture   *textures[8];    // Textures for each animation frame (8 in this case)
}               t_door;
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
	t_texture *texture1;
	t_texture *texture2;
	t_texture *texture3;
	t_texture *texture4;
	t_texture *texture_art1;
	t_texture *texture_art2;
	t_texture *player[14];
	t_texture *doors[8];
	t_texture *current_door_texture;
	t_texture *logo;
	t_texture *press_to_start;
	t_texture *you_died;
	t_texture *mini_map;
	t_texture *icon_player;
	// t_tex	*tex;
	t_door *door;
	t_ray *ray;
	t_player *ply;
	t_sprite *sprites;
	t_sound sounds[5];
	game_state state;
	int frame;
	int flag;
} t_data;

typedef struct s_wall_params {
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
t_inter get_h_inter(t_data *data, float angl);
t_inter get_v_inter(t_data *data, float angl);
double normalize_angle(double angle);
double calculate_distance(t_data *data, float angle);
void start_h_y(t_data *data, double angl, double *h_y);
void start_v_x(t_data *data, double angl, double *v_x);
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
void render_wall(t_data *data, int x);
void drawing_3d_game(t_data *data);
t_texture *texture_loader(t_data *data, char *texture_path);
void set_floor_coords(t_data *data, int ray);
void floor_casting(t_data *data, int x);
int get_pixel_from_texture(t_texture *texture, int offset_x, int offset_y);
t_texture *png_texture_loader(t_data *data, char *texture_path);
int mouse_move(int x, int y, t_data *data);
int mouse_release(int button, int x, int y, t_data *data);
void render_sprites(t_data *data);
double ft_distance(t_data *data, double x, double y);
t_wall_params calculate_wall_params(t_data *data);
void load_door_textures(t_data *data);
void rendring_door(t_data *data, t_door door, int x);
void update_door_animation(t_data *data, t_door *door, double current_time);
int get_start_drawing_texture_x(t_ray ray);
bool player_in_grid(t_data *data);
void start_h_y_door(t_data *data, double angl, double *h_y);
void Head_Bobbing(t_data *data);
#endif
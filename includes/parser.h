#ifndef PARSER_H
#define PARSER_H

#include "./cub3d.h"
typedef struct s_args t_args;
typedef struct s_rgb t_rgb;

int check_surroundings(char **map_lines, int i, int j);
int is_file_path_valid(char *file_path);
char **file_to_arr(char *file_path);

void texture_path_extracter(char *line, t_args *cub3d_args);
void rgb_extracter(char *line, t_rgb *rgb);

void parser(int ac, char **av, t_args *cub3d_args);

#endif
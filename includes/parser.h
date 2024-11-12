/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:28:20 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/11 23:42:17 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./cub3d.h"

typedef struct s_args	t_args;
typedef struct s_rgb	t_rgb;

typedef enum direction
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
}						t_direction;

typedef struct s_wallFrame
{
	int					x;
	int					y;
	t_direction			direction;
	int					frame;
}						t_wall_frame;

typedef struct s_wall_door
{
	int					i;
	int					j;
	bool				is_open;
	int					current_frame;
	double				last_update_time;
}						t_wall_door;

int				check_surroundings(char **map_lines, int i, int j);
int				is_file_path_valid(char *file_path);
char			**file_to_arr(t_args *args, char *file_path);
void			texture_path_extracter(char *line, t_args *cub3d_args);
void			rgb_extracter(t_args *args, char *line, t_rgb *rgb);
void			parser(int ac, char **av, t_args *cub3d_args);
int				get_taller_line(char **map_lines);
void			set_map_metadata(t_args *args);
void			remove_empty(char **map_lines);
int				get_taller_line(char **map_lines);
void			add_doors(t_args *cub_args);
void			add_wall_frames(t_args *cub_args);
char			*fill_extra(char *line, int max_len);
t_wall_frame	*fill_frame_struct(char **map_lines, int x, int y);
bool			is_logic_frame_helper(char pos);
bool			is_logic_frame(t_args *cub_args, int y, int x);
bool			is_texture(char *line);
void			init_wallframes_struct(t_args *cub_args);
void init_structs_args(t_args *args);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:04:23 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/13 02:36:56 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_wall_frame	*fill_frame_struct(char **map_lines, int x, int y)
{
	t_wall_frame	*frame;
	int				available_directions[4];
	int				max_rows;
	int				count;

	max_rows = 0;
	count = 0;
	frame = malloc(sizeof(t_wall_frame));
	frame->x = x;
	frame->y = y;
	frame->frame = rand() % 2 + 1;
	while (map_lines[max_rows++])
		;
	max_rows--;
	if ((x + 1) < (ft_strlen(map_lines[0]) - 1) && map_lines[y][x + 1] == '0')
		available_directions[count++] = RIGHT;
	if ((x - 1 >= 0) && map_lines[y][x - 1] == '0')
		available_directions[count++] = LEFT;
	if ((y - 1) >= 0 && map_lines[y - 1][x] == '0')
		available_directions[count++] = TOP;
	if ((y + 1) < max_rows && map_lines[y + 1][x] == '0')
		available_directions[count++] = BOTTOM;
	if (count > 0)
		frame->direction = available_directions[rand() % count];
	return (frame);
}

void	init_wallframes_struct(t_args *cub_args)
{
	int			frame_number;
	int			x;
	int			y;

	frame_number = 0;
	y = 0;
	cub_args->frames = malloc(sizeof(t_wall_frame *)
			* (cub_args->number_of_frames + 1));
	if (!cub_args->frames)
		return ;
	cub_args->frames[cub_args->number_of_frames] = NULL;
	while (cub_args->map_lines[y])
	{
		x = 0;
		while (cub_args->map_lines[y][x])
		{
			if (cub_args->map_lines[y][x] == 'F')
				cub_args->frames[frame_number++]
					= fill_frame_struct(cub_args->map_lines, x, y);
			x++;
		}
		y++;
	}
}

bool	is_logic_frame_helper(char pos)
{
	return (pos == 'k' || pos == '1' || pos == 'D' || pos == 'F' || pos == 'X');
}

bool	is_texture(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0);
}

bool	is_logic_frame(t_args *cub_args, int y, int x)
{
	char	left_side;
	char	right_side;
	char	top_side;
	char	bottom_side;

	if (x - 1 >= 0)
		left_side = cub_args->map_lines[y][x - 1];
	else
		left_side = 'k';
	if (x + 1 < cub_args->map_columns)
		right_side = cub_args->map_lines[y][x + 1];
	else
		right_side = 'k';
	if (y + 1 < cub_args->map_rows)
		bottom_side = cub_args->map_lines[y + 1][x];
	else
		bottom_side = 'k';
	if (y - 1 >= 0)
		top_side = cub_args->map_lines[y - 1][x];
	else
		top_side = 'k';
	return (!is_logic_frame_helper(left_side)
		|| !is_logic_frame_helper(right_side)
		|| !is_logic_frame_helper(top_side)
		|| !is_logic_frame_helper(bottom_side));
}

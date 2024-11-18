/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:45:21 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/18 07:10:01 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	parse_top_bottom_lines(t_args *args, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			ft_error(args, "Map is not closed/surrounded by walls.",
				true, true);
		i++;
	}
}

static int	parse_middle_lines(t_args *args, char **lines,
	int i, int j)
{
	char	*tmp;
	char	*line;

	line = lines[i];
	while (line[j])
	{
		tmp = ft_strtrim(line, " ");
		if ((j == 0 && tmp[j] != '1') || (j == (int)ft_strlen(line) - 1
				&& tmp[j] != '1'))
			return (free(tmp),
				ft_error(args, "Map error.", true, true));
		if (tmp[j] != 'D' && tmp[j] != '1' && tmp[j] != '0' && tmp[j] != 'N'
			&& tmp[j] != 'S' && tmp[j] != 'E' && tmp[j] != 'W' && tmp[j] != ' ')
			return (free(tmp), ft_error(args, "Invalid map character.",
					true, true));
		if (tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E' || tmp[j] == 'W')
			args->player_count++;
		if (tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E'
			|| tmp[j] == 'W')
			if (check_surroundings(lines, i, j))
				return (free(tmp),
					ft_error(args, "Map error.", true, true));
		j++;
		free(tmp);
	}
	return (1);
}

static void	parse_map2d(t_args *args, char **map2d)
{
	int	i;
	int	j;

	i = 0;
	args->player_count = 0;
	while (map2d[i])
	{
		j = 0;
		if (i == 0 || !map2d[i + 1])
			parse_top_bottom_lines(args, map2d[i]);
		else
			parse_middle_lines(args, map2d, i, j);
		i++;
	}
	if (args->player_count != 1)
		ft_error(args, "Invalid number of players.", true, true);
}

static void	parse_file_lines(t_args *args, char **file_lines)
{
	int		i;
	char	*curr_line;

	i = 0;
	if (!file_lines)
		ft_error(args, "Map is empty!", 1, 0);
	while (file_lines[i])
	{
		curr_line = ft_strtrim(file_lines[i], " ");
		if (is_texture(curr_line))
			texture_path_extracter(curr_line, args);
		else if (ft_strncmp(curr_line, "F", 1) == 0)
			rgb_extracter(args, curr_line + 1, &args->floor_color);
		else if (ft_strncmp(curr_line, "C", 1) == 0)
			rgb_extracter(args, curr_line + 1, &args->ceiling_color);
		else if (curr_line == NULL)
			i++;
		else if (curr_line[0] == '1' && (free(curr_line), 1))
			break ;
		else if ((free(curr_line), 1))
			ft_error(args, "Invalid Identifier.", true, true);
		i++;
	}
	args->map2d = file_lines + i;
}

void	parser(int ac, char **av, t_args *cub3d_args)
{
	if (ac != 2)
		ft_error(cub3d_args, "invalid number of arguments.", true, false);
	if (!is_file_path_valid(av[1]))
		ft_error(cub3d_args, "invalid map extension.", true, false);
	ft_memset(cub3d_args, 0, sizeof(t_args));
	cub3d_args->file_lines = file_to_arr(cub3d_args, av[1]);
	parse_file_lines(cub3d_args, cub3d_args->file_lines);
	parse_map2d(cub3d_args, cub3d_args->map2d);
	remove_empty(cub3d_args->map2d);
	set_map_metadata(cub3d_args);
	add_doors(cub3d_args);
	add_wall_frames(cub3d_args);
	init_wallframes_struct(cub3d_args);
}

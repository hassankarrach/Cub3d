/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:06:45 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 18:07:59 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_surroundings(char **map_lines, int i, int j)
{
	return (map_lines[i - 1][j] == ' ' || map_lines[i + 1][j] == ' ' ||
			map_lines[i][j - 1] == ' ' || map_lines[i][j + 1] == ' ');
}

int	is_file_path_valid(char *file_path)
{
	char	*file_ext;

	file_ext = ft_strrchr(file_path, '.');
	if (!file_ext)
		return (0);
	if (ft_strlen(file_ext) != 4)
		return (0);
	return (!ft_strncmp(file_ext, ".cub", 4));
}

char	**file_to_arr(t_args *args, char *file_path)
{
	int		fd;
	char	*curr_line;
	char	*full_lines;
	char	**lines;
	char	*tmp;

	full_lines = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		ft_error(args, "cannot open the map file.", true, false);
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		tmp = ft_strjoin(full_lines, curr_line);
		free(curr_line);
		full_lines = tmp;
		curr_line = get_next_line(fd);
	}
	lines = ft_split(full_lines, '\n');
	free(full_lines);
	return (lines);
}

void	remove_empty(char **map_lines)
{
	int		i;
	int		j;
	int		curr_line_len;
	int		taller_line;
	char	*tmp;

	i = 0;
	taller_line = get_taller_line(map_lines);
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == ' ')
				map_lines[i][j] = 'X';
			j++;
		}
		if (ft_strlen(map_lines[i]) < taller_line)
			map_lines[i] = fill_extra(map_lines[i], taller_line);
		i++;
	}
}

int	get_taller_line(char **map_lines)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (map_lines[i])
	{
		if (ft_strlen(map_lines[i]) > max_len)
			max_len = ft_strlen(map_lines[i]);
		i++;
	}
	return (max_len);
}

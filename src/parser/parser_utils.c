/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:06:45 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/19 05:51:23 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int check_surroundings(char **map2d, int i, int j)
{
    int rows = 0;
    int cols = 0;
    
    while (map2d[rows] != NULL)
        rows++;
    
    if (map2d[0] != NULL)
    {
        while (map2d[0][cols] != '\0')
            cols++;
    }
    
    if (i > 0 && map2d[i - 1][j] == ' ')
        return 1;

    if (i < rows - 1 && map2d[i + 1][j] == ' ')
        return 1;

    if (j > 0 && map2d[i][j - 1] == ' ')
        return 1;

    if (j < cols - 1 && map2d[i][j + 1] == ' ')
        return 1;
    return 0;
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
		free(full_lines);
		full_lines = tmp;
		curr_line = get_next_line(fd);
	}
	lines = ft_split(full_lines, '\n');
	free(full_lines);
	return (lines);
}

void	remove_empty(char **map2d)
{
	int		i;
	int		j;
	int		taller_line;

	i = 0;
	taller_line = get_taller_line(map2d);
	while (map2d[i])
	{
		j = 0;
		while (map2d[i][j])
		{
			if (map2d[i][j] == ' ')
				map2d[i][j] = 'X';
			j++;
		}
		if (ft_strlen(map2d[i]) < (size_t)taller_line)
			map2d[i] = fill_extra(map2d[i], taller_line);
		i++;
	}
}

int	get_taller_line(char **map2d)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (map2d[i])
	{
		if (ft_strlen(map2d[i]) > (size_t)max_len)
			max_len = ft_strlen(map2d[i]);
		i++;
	}
	return (max_len);
}

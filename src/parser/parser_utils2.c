/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:08:20 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 22:16:44 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// Parser utils.
void	set_map_metadata(t_args *args)
{
	int	rows;

	rows = 0;
	while (args->map_lines[rows])
		rows++;
	args->map_rows = rows;
	args->map_columns = get_taller_line(args->map_lines);
}

void	texture_path_extracter(char *line, t_args *cub3d_args)
{
	char	*value;
	char	*texture_extension;

	value = ft_strtrim(line + 2, " ");
	texture_extension = ft_strrchr(value, '.');
	if (value[0] != '.' || !(ft_strlen(texture_extension) == 4
			&& ft_strncmp(texture_extension, ".xpm", 4) == 0))
	{
		free(line);
		ft_error(cub3d_args, "invalid texture file path.", true, true);
	}
	if (ft_strncmp(line, "NO", 2) == 0 && !cub3d_args->North_texture)
		cub3d_args->North_texture = value;
	else if (ft_strncmp(line, "SO", 2) == 0 && !cub3d_args->South_texture)
		cub3d_args->South_texture = value;
	else if (ft_strncmp(line, "WE", 2) == 0 && !cub3d_args->West_texture)
		cub3d_args->West_texture = value;
	else if (ft_strncmp(line, "EA", 2) == 0 && !cub3d_args->East_texture)
		cub3d_args->East_texture = value;
	else
	{
		free(line);
		ft_error(cub3d_args, "duplicated Idf(SO, WE, EA, NO)", true, true);
	}
	free(line);
}

static void	is_valid_rgb(t_args *args, char **rgb)
{
	int		i;
	int		j;
	char	*trimmed_prop;
	int		rgb_value;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		trimmed_prop = ft_strtrim(rgb[i], " ");
		while (trimmed_prop[j])
		{
			if (!(trimmed_prop[j] >= '0' && trimmed_prop[j] <= '9'))
				ft_error(args, "invalid RGB prop!", true, true);
			j++;
		}
		rgb_value = ft_atoi(trimmed_prop);
		free(trimmed_prop);
		if (j > 3 || rgb_value < 0 || rgb_value > 255)
			ft_error(args, "invalid RGB prop!", true, true);
		i++;
	}
	if (i != 3)
		ft_error(args, "Invalid RGB color.", true, true);
}

void	rgb_extracter(t_args *args, char *line, t_rgb *rgb)
{
	char	*trimmed_line;
	char	**extracted_rgb;

	trimmed_line = ft_strtrim(line, " ");
	if (trimmed_line[0] == ','
		|| trimmed_line[ft_strlen(trimmed_line) - 1] == ',')
		ft_error(args, "Invalid RGB color.", true, true);
	free(line - 1);
	extracted_rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (rgb->r || rgb->g || rgb->b)
		ft_error(args, "Duplicated Floor or Ceiling color Identifier!", true,
			true);
	is_valid_rgb(args, extracted_rgb);
	rgb->r = ft_atoi(extracted_rgb[0]);
	rgb->g = ft_atoi(extracted_rgb[1]);
	rgb->b = ft_atoi(extracted_rgb[2]);
	free(extracted_rgb[0]);
	free(extracted_rgb[1]);
	free(extracted_rgb[2]);
	free(extracted_rgb);
}

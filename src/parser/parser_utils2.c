#include "../../includes/parser.h"

// Parser utils.
void set_map_metadata(t_args *args)
{
	int rows;

	rows = 0;
	while (args->map_lines[rows])
		rows++;
	args->map_rows = rows;
	args->map_columns = get_taller_line(args->map_lines);
}

void texture_path_extracter(char *line, t_args *cub3d_args)
{
	char *value;
	char *texture_extension;

	value = ft_strtrim(line + 2, " ");
	texture_extension = ft_strrchr(value, '.');
	if (value[0] != '.' ||
		!(ft_strlen(texture_extension) == 4 && ft_strncmp(texture_extension, ".xpm", 4) == 0))
		ft_error("invalid texture file path.");

	if (ft_strncmp(line, "NO", 2) == 0 && !cub3d_args->North_texture)
		cub3d_args->North_texture = value;
	else if (ft_strncmp(line, "SO", 2) == 0 && !cub3d_args->South_texture)
		cub3d_args->South_texture = value;
	else if (ft_strncmp(line, "WE", 2) == 0 && !cub3d_args->West_texture)
		cub3d_args->West_texture = value;
	else if (ft_strncmp(line, "EA", 2) == 0 && !cub3d_args->East_texture)
		cub3d_args->East_texture = value;
	else
		ft_error("a duplicated Identifier (SO, WE, EA, NO)");
}
static void is_valid_rgb(char **rgb)
{
	int i;
	int j;
	char *trimmed_prop;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		trimmed_prop = ft_strtrim(rgb[i], " ");
		while (trimmed_prop[j])
		{
			if (!(trimmed_prop[j] >= '0' && trimmed_prop[j] <= '9'))
				ft_error("invalid RGB prop!");
			j++;
		}
		if (j > 3)
			ft_error("invalid RGB prop!");
		i++;
	}
	if (i != 3)
		ft_error("Invalid RGB color.");
}
void rgb_extracter(char *line, t_rgb *rgb)
{
	char *trimmed_line;
	char **extracted_rgb;

	trimmed_line = ft_strtrim(line, " ");
	extracted_rgb = ft_split(trimmed_line, ',');

	if (rgb->r || rgb->g || rgb->b)
		ft_error("Duplicated Floor or Ceiling color Identifier!");
	is_valid_rgb(extracted_rgb);
	rgb->r = ft_atoi(extracted_rgb[0]);
	rgb->g = ft_atoi(extracted_rgb[1]);
	rgb->b = ft_atoi(extracted_rgb[2]);
}

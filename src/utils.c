#include "../includes/cub3d.h"

// Parser utils.
void texture_path_extracter(char *line, char **to_be_filled)
{
	char *value;
	char *texture_extension;

	value = ft_strtrim(line, " ");
	texture_extension = ft_strrchr(value, '.');
	if (*to_be_filled)
		ft_error("a duplicated Identifier (SO, WE, EA, NO)");
	if (value[0] != '.' ||
		!(ft_strlen(texture_extension) == 4 && ft_strncmp(texture_extension, ".xpm", 4) == 0))
		ft_error("invalid texture file path.");

	*to_be_filled = value;
}
static void	is_valid_rgb(char **rgb)
{
	int		i;
	int		j;
	char	*trimmed_prop;

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

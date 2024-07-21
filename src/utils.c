#include "../includes/cub3d.h"

// Parser utils.
char *texture_path_extracter(char *line)
{
    char *value;
    char *texture_extension;

    value = ft_strtrim(line, " ");
    texture_extension = ft_strrchr(value, '.');
    if (value[0] != '.' ||
        !(ft_strlen(texture_extension) == 4 && ft_strncmp(texture_extension, ".xpm", 4) == 0))
        ft_error("invalid texture file path.");
    return (value);
}

void    rgb_extracter(char *line, t_args *cub3d_args, char flag)
{
    char *trimmed_line;
    char **rgb;

    trimmed_line = ft_strtrim(line, " ");
    rgb = ft_split(trimmed_line, ',');

    if (flag == 'C')
    {
        cub3d_args->Ceiling_color.r = ft_atoi(rgb[0]);
        cub3d_args->Ceiling_color.g = ft_atoi(rgb[1]);
        cub3d_args->Ceiling_color.b = ft_atoi(rgb[2]);
    }
    else if (flag == 'F')
    {
        cub3d_args->Floor_color.r = ft_atoi(rgb[0]);
        cub3d_args->Floor_color.g = ft_atoi(rgb[1]);
        cub3d_args->Floor_color.b = ft_atoi(rgb[2]);
    }
}
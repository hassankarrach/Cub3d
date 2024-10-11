#include "../../includes/parser.h"

static void parse_top_bottom_lines(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
            ft_error("Map is not closed/surrounded by walls.");
        i++;
    }
}
static void parse_middle_lines(char **lines, char *line, int i, int j, int *player_count)
{
    while (line[j])
    {
        char *tmp = ft_strtrim(line, " ");
        if ((j == 0 && tmp[j] != '1') || (j == (int)ft_strlen(line) - 1 && tmp[j] != '1'))
            ft_error("Map is not closed/surrounded by walls.");
        if (tmp[j] != 'D' && tmp[j] != '1' && tmp[j] != '0' && tmp[j] != 'N' && tmp[j] != 'S' && tmp[j] != 'E' && tmp[j] != 'W' && tmp[j] != ' ')
            ft_error("Invalid map character.");
        if (tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E' || tmp[j] == 'W')
            (*player_count)++;
        if (tmp[j] == '0' || tmp[j] == 'N' || tmp[j] == 'S' || tmp[j] == 'E' || tmp[j] == 'W')
        {
            if (check_surroundings(lines, i, j))
                ft_error("Map is not closed/surrounded by walls.");
        }
        j++;
    }
}
static void parse_map_lines(char **map_lines)
{
    int i;
    int j;
    int player_count;

    i = 0;
    player_count = 0;
    while (map_lines[i])
    {
        j = 0;
        if (i == 0 || !map_lines[i + 1])
            parse_top_bottom_lines(map_lines[i]);
        else
            parse_middle_lines(map_lines, map_lines[i], i, j, &player_count);
        i++;
    }
    if (player_count != 1)
        ft_error("Invalid number of players.");
}
static void parse_file_lines(t_args *cub3d_args, char **file_lines)
{
    int i;
    char *curr_line;

    i = 0;
    while (file_lines[i])
    {
        curr_line = ft_strtrim(file_lines[i], " ");
        if (ft_strncmp(curr_line, "NO", 2) == 0 || ft_strncmp(curr_line, "SO", 2) == 0 || ft_strncmp(curr_line, "WE", 2) == 0 || ft_strncmp(curr_line, "EA", 2) == 0)
            texture_path_extracter(curr_line, cub3d_args);
        else if (ft_strncmp(curr_line, "F", 1) == 0)
            rgb_extracter(curr_line + 1, &cub3d_args->Floor_color);
        else if (ft_strncmp(curr_line, "C", 1) == 0)
            rgb_extracter(curr_line + 1, &cub3d_args->Ceiling_color);
        else if (curr_line == NULL)
            i++;
        else if (curr_line[0] == '1')
            break;
        else
            ft_error("Invalid Identifier.");
        i++;
    }
    cub3d_args->map_lines = file_lines + i;
}
static int get_taller_line(char **map_lines)
{
    int i;
    int max_len;

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
static char *fill_extra(char *line, int max_len)
{
    int curr_line_len;
    char *tmp;
    char *res;

    curr_line_len = ft_strlen(line);
    res = ft_strdup(line);
    while (max_len > (curr_line_len))
    {
        tmp = ft_strjoin(res, "X");
        free(res);
        res = tmp;
        curr_line_len++;
    }
    return (res);
}
static void remove_empty(char **map_lines)
{
    int i;
    int j;
    int curr_line_len;
    int taller_line;
    char *tmp;

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

void parser(int ac, char **av, t_args *cub3d_args)
{
    char **file_lines;

    if (ac != 2)
        ft_error("invalid number of arguments.");
    if (!is_file_path_valid(av[1]))
        ft_error("invalid map extension.");
    ft_memset(cub3d_args, 0, sizeof(t_args));
    file_lines = file_to_arr(av[1]);
    parse_file_lines(cub3d_args, file_lines);
    parse_map_lines(cub3d_args->map_lines);
    remove_empty(cub3d_args->map_lines);
}

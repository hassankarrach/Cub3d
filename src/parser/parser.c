#include "../../includes/parser.h"

static void add_doors(t_args *cub_args)
{
    int i;
    int j;
    int doors_count;

    i = 0;
    doors_count = 3;
    while (cub_args->map_lines[i] && doors_count)
    {
        j = 0;
        // don't add 2 doors beside each other
        while (cub_args->map_lines[i][j] && doors_count)
        {
            if (cub_args->map_lines[i][j] == '0')
            {
                if (cub_args->map_lines[i - 1][j] == '1' && cub_args->map_lines[i + 1][j] == '1' && cub_args->map_lines[i][j - 1] != 'D' && cub_args->map_lines[i][j + 1] != 'D')
                {
                    cub_args->map_lines[i][j] = 'D';
                    doors_count--;
                }
                else if (cub_args->map_lines[i][j - 1] == '1' && cub_args->map_lines[i][j + 1] == '1' && cub_args->map_lines[i - 1][j] != 'D' && cub_args->map_lines[i + 1][j] != 'D')
                {
                    cub_args->map_lines[i][j] = 'D';
                    doors_count--;
                }
            }
            j++;
        }
        i++;
    }
}

static t_wallFrame *fill_frame_struct(char **map_lines, int x, int y) // use this to fill later.
{
    t_wallFrame *frame;

    frame = malloc(sizeof(t_wallFrame));
    frame->x = x;
    frame->y = y;
    frame->Frame = rand() % 2 + 1;

    int available_directions[4];
    int max_rows = 0;
    int count = 0;

    while (map_lines[max_rows++])
        ;
    max_rows--;

    if ((x + 1) < (ft_strlen(map_lines[0] - 1)) && map_lines[y][x + 1] == '0')
        available_directions[count++] = RIGHT;

    if ((x - 1 >= 0) && map_lines[y][x - 1] == '0')
        available_directions[count++] = LEFT;

    if ((y - 1) >= 0 && map_lines[y - 1][x] == '0')
        available_directions[count++] = TOP;

    if ((y + 1) < max_rows && map_lines[y + 1][x] == '0')
        available_directions[count++] = BOTTOM;

    if (count > 0)
    {
        int random_index = rand() % count;
        frame->direction = available_directions[random_index];
    }
    return (frame);
}

const char *directionToString(e_Direction direction)
{
    const char *directionStrings[] = {
        "TOP",
        "BOTTOM",
        "LEFT",
        "RIGHT"};
    return directionStrings[direction];
}

static void init_wallFrames_struct(t_args *cub_args)
{
    t_wallFrame **frames;
    int number_of_rows;
    int frame_number;
    int x;
    int y;

    frame_number = 0;
    number_of_rows = 0;
    y = 0;
    while (cub_args->map_lines[number_of_rows++])
        ;
    number_of_rows--;
    frames = malloc(sizeof(t_wallFrame *) * (cub_args->number_of_frames + 1));
    if (!frames)
        return;
    frames[cub_args->number_of_frames] = NULL;

    frames[0] = fill_frame_struct(cub_args->map_lines, 0, 0);

    int count = 0;
    while (cub_args->map_lines[y])
    {
        x = 0;
        while (cub_args->map_lines[y][x])
        {
            if (cub_args->map_lines[y][x] == 'F')
            {
                frames[frame_number] = fill_frame_struct(cub_args->map_lines, x, y);
                frame_number++;
            }
            x++;
        }
        y++;
    }


    cub_args->frames = frames;
}
static bool is_logic_frame_helper(char pos)
{
    return (pos == 'k' || pos == '1' || pos == 'D' || pos == 'F' || pos == 'X');
}
static bool is_logic_frame(t_args *cub_args, int y, int x)
{
    char left_side;
    char right_side;
    char top_side;
    char bottom_side;
    int max_rows;
    int max_columns;

    max_columns = cub_args->map_columns;
    max_rows = cub_args->map_rows;
    if (x - 1 >= 0)
        left_side = cub_args->map_lines[y][x - 1];
    else
        left_side = 'k';
    if (x + 1 < max_columns)
        right_side = cub_args->map_lines[y][x + 1];
    else
        right_side = 'k';
    if (y + 1 < max_rows)
        bottom_side = cub_args->map_lines[y + 1][x];
    else
        bottom_side = 'k';
    if (y - 1 >= 0)
        top_side = cub_args->map_lines[y - 1][x];
    else
        top_side = 'k';
    return (!is_logic_frame_helper(left_side) || !is_logic_frame_helper(right_side) || !is_logic_frame_helper(top_side) || !is_logic_frame_helper(bottom_side));
}

static void add_wall_frames(t_args *cub_args)
{
    int frames_per_row;
    int i;
    int j;
    cub_args->number_of_frames = 0;

    i = 0;
    frames_per_row = 2;
    while (cub_args->map_lines[i])
    {
        j = 0;
        frames_per_row = 2;
        while (cub_args->map_lines[i][j])
        {
            if (cub_args->map_lines[i][j] == '1' && frames_per_row && is_logic_frame(cub_args, i, j) && j != 0 && j < cub_args->map_columns && i != 0 && i < (cub_args->map_rows - 1))
            {
                cub_args->map_lines[i][j] = 'F';
                cub_args->number_of_frames++;
                frames_per_row--;
            }
            j++;
        }
        i++;
    }
}
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
int get_taller_line(char **map_lines)
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
    set_map_metadata(cub3d_args);
    add_doors(cub3d_args);
    add_wall_frames(cub3d_args);
    init_wallFrames_struct(cub3d_args);

    // =====Debug======
    // int i = 0;
    // while (cub3d_args->map_lines[i])
    //     printf("%s\n", cub3d_args->map_lines[i++]);
    // i = 0;
    // while (cub3d_args->frames[i])
    // {
    //     printf("%s [%d-%d] %d\n", directionToString(cub3d_args->frames[i]->direction), cub3d_args->frames[i]->y, cub3d_args->frames[i]->x, cub3d_args->frames[i]->Frame);
    //     i++;
    // }
}

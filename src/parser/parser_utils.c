#include "../../includes/parser.h"

int check_surroundings(char **map_lines, int i, int j)
{
    return (map_lines[i - 1][j] == ' ' || map_lines[i + 1][j] == ' ' ||
            map_lines[i][j - 1] == ' ' || map_lines[i][j + 1] == ' ');
}

int is_file_path_valid(char *file_path)
{
    char *file_ext;

    file_ext = ft_strrchr(file_path, '.');
    if (!file_ext)
        return 0;
    if (ft_strlen(file_ext) != 4)
        return (0);
    return (!ft_strncmp(file_ext, ".cub", 4));
}

char **file_to_arr(char *file_path)
{
    int fd;
    char *curr_line;
    char *full_lines;

    full_lines = NULL;
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        ft_error("cannot open the map file.");
    curr_line = get_next_line(fd);
    while (curr_line)
    {
        full_lines = ft_strjoin(full_lines, curr_line);
        curr_line = get_next_line(fd);
    }
    return (ft_split(full_lines, '\n'));
}


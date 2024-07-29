#include "../includes/cub3d.h"

static int is_file_path_valid(char *file_path)
{
	char *file_ext;

	file_ext = ft_strrchr(file_path, '.');
	if (!file_ext)
		return 0;
	if (ft_strlen(file_ext) != 4)
		return (0);
	return (!ft_strncmp(file_ext, ".cub", 4));
}

static char **file_to_arr(char *file_path)
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

static void parse_file_lines(t_args *cub3d_args, char **file_lines)
{
	int		i;
	char	*curr_line;

	i = 0;
	while (file_lines[i])
	{
		curr_line = ft_strtrim(file_lines[i], " ");
		if (ft_strncmp(curr_line, "NO", 2) == 0)
			texture_path_extracter(curr_line + 2, &cub3d_args->North_texture);
		else if (ft_strncmp(curr_line, "SO", 2) == 0)
			texture_path_extracter(curr_line + 2, &cub3d_args->South_texture);
		else if (ft_strncmp(curr_line, "WE", 2) == 0)
			texture_path_extracter(curr_line + 2, &cub3d_args->West_texture);
		else if (ft_strncmp(curr_line, "EA", 2) == 0)
			texture_path_extracter(curr_line + 2, &cub3d_args->East_texture);
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
}

/*
	RULES ==>
	◦ only 6 possible characters:
		0 for an empty space.
		1 for a wall.
		N,S,E or W for the player’s start position and spawning orientation.
	◦ The map must be closed/surrounded by walls, if not the program must return
		an error.
	◦ Except for the map content, each type of element can be separated by one or
		more empty line(s).
	◦ Except for the map content which always has to be the last, each type of
		element can be set in any order in the file.
	◦ Except for the map, each type of information from an element can be separated
		by one or more space(s).
	◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
		map and are up to you to handle. You must be able to parse any kind of map,
		as long as it respects the rules of the map.
*/
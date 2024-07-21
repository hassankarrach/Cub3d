#include "../includes/cub3d.h"

static int	is_file_path_valid(char *file_path)
{
	char	*file_ext;

	file_ext = ft_strrchr(file_path, '.');
	if (!file_ext)
		return 0;
	if ( ft_strlen(file_ext) != 4)
		return (0);
	return (!ft_strncmp(file_ext, ".cub", 4));
}

static  char **file_to_arr(char *file_path)
{
	int		fd;
	char	*curr_line;
	char	*full_lines;

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

void    parser(int ac, char **av)
{
	char	**map_lines;

	if (ac != 2)
		ft_error("invalid number of arguments.");
	if (!is_file_path_valid(av[1]))
		ft_error("invalid map extension.");
	map_lines = file_to_arr(av[1]);
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
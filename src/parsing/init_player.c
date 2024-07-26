#include "../includes/cub3d.h"

void	get_x_y_player(t_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->args->map_lines[i])
	{
		j = 0;
		while (m->args->map_lines[i][j])
		{
			if (m->args->map_lines[i][j] == 'N' || m->args->map_lines[i][j] == 'S'
				|| m->args->map_lines[i][j] == 'W' || m->args->map_lines[i][j] == 'E')
			{
				m->p_x = j;
				m->p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
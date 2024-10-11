#include "../../includes/cub3d.h"

void get_angle(t_data *m)
{
	if (m->ply->player_dir == 'N')
	{
		m->ply->dir_x = 0;
		m->ply->dir_y = -1;
		m->ply->angle = 3 * M_PI / 2;
		m->ply->plane_x = 0;
		m->ply->plane_y = tan(FOV / 2 * DEG_TO_RAD);
	}
	else if (m->ply->player_dir == 'S')
	{
		m->ply->dir_x = 0;
		m->ply->dir_y = 1;
		m->ply->angle = M_PI / 2;
		m->ply->plane_x = 0;
		m->ply->plane_y = -tan(FOV / 2 * DEG_TO_RAD);
	}
	else if (m->ply->player_dir == 'W')
	{
		m->ply->dir_x = -1;
		m->ply->dir_y = 0;
		m->ply->angle = M_PI;
		m->ply->plane_x = tan(FOV / 2 * DEG_TO_RAD);
		m->ply->plane_y = 0;
	}
	else if (m->ply->player_dir == 'E')
	{
		m->ply->dir_x = 1;
		m->ply->dir_y = 0;
		m->ply->angle = 0;
		// printf ("jj\n");
		// printf ("%f\n", m->ply->angle);
		m->ply->plane_x = -tan(FOV / 2 * DEG_TO_RAD);
		m->ply->plane_y = 0;
	}
}
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
				m->ply->player_dir = m->args->map_lines[i][j];
				m->index_x = j;
				m->index_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
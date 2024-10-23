#include "../../includes/raycaster.h"

bool	get_door_inter_h(t_data *data, t_inter *inter_h, double x_step,
		double y_step)
{
	double	save_inter_x;
	double	save_inter_y;

	save_inter_x = inter_h->xintercept;
	save_inter_y = inter_h->yintercept;
	if (player_in_grid(data))
	{
		start_h_y_door(data, data->ray->ray_ngl, &inter_h->yintercept);
		inter_h->xintercept = data->ply->posX + (inter_h->yintercept
				- data->ply->posY) / tan(data->ray->ray_ngl);
		if (fmod(data->ply->posY, TILE_SIZE) < TILE_SIZE / 2
			&& is_ray_facing_up(data->ray->ray_ngl))
		{
			inter_h->xintercept = save_inter_x;
			inter_h->yintercept = save_inter_y;
			return (false);
		}
		return (true);
	}
	inter_h->xintercept += x_step / 2;
	inter_h->yintercept += y_step / 2;
	return (false);
}

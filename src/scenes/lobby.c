#include "../../includes/cub3d.h"

void lobby(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->logo->img, 250, 200);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->press_to_start->img, 250, (S_H - 150));

	// printf("%s\n", data->sounds[0].file_path);

	// stop_all_sounds(data);
	if (!data->sounds[0].is_playing)
		play_sound(&data->sounds[0]);
}

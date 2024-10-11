#include "../../includes/scenes.h"

void lobby(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->textures.logo->img, 250, 200);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->textures.press_to_start->img, 250, (S_H - 150));
	// stop_all_sounds(data);
	// if (!data->sounds[0].is_playing)
	// 	play_sound(&data->sounds[0]);
}

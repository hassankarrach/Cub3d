#include "../../includes/scenes.h"

void game_pause(t_data *data)
{
	mlx_string_put(data->mlx->mlx, data->mlx->win, S_W / 2 - 50, S_H / 2, 0x00FFFFFF, "PAUSED");
}
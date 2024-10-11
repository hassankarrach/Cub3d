#include "../../includes/scenes.h"

void you_died(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->textures.you_died->img, 400, 400);
}
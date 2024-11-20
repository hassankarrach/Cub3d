/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:16:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/19 21:48:35 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_texture(t_player *ply)
{
	ply->current_frame = 0;
	ply->total_frames = 24;
	ply->last_update_time = 0;
}

void	init_ray(t_ray *ray)
{
	ray->ray_ngl = 0;
	ray->hit_door = 0;
	ray->skip_door = 0;
	ray->distance = 0;
	ray->v_or_h = 0;
	ray->wall_height = 0;
	ray->min_inter.is_door = 0;
	ray->min_inter.xintercept = 0;
	ray->min_inter.yintercept = 0;
}

void	load_player_textures(t_data *data)
{
	int		i;
	char	*full_path;
	char	*tmp;
	char	*texture_id;

	i = 1;
	while (i <= 24)
	{
		texture_id = ft_itoa(i);
		full_path = ft_strjoin("./assets/player/player_", texture_id);
		free(texture_id);
		tmp = full_path;
		full_path = ft_strjoin(full_path, ".xpm");
		data->textures.player[i - 1] = texture_loader(data, full_path);
		free(tmp);
		free(full_path);
		i++;
	}
}

void	init_doors(t_data *data, t_door *door)
{
	int	i;

	door->is_open = 0;
	door->distance = sqrt(pow(data->w_map * TILE_SIZE, 2) + pow(data->h_map
				* TILE_SIZE, 2));
	door->current_frame = 0;
	door->total_frames = 26;
	door->last_update_time = 0;
	door->doors = data->args->doors;
	i = 0;
	while (i < 3 && door->doors[i])
	{
		door->doors[i]->last_update_time = 0;
		door->doors[i]->is_open = 0;
		door->doors[i]->current_frame = 0;
		i++;
	}
}

void	init_game(t_data *data, t_args *args)
{
	data->map2d = args->map2d;
	data->args = args;
	data->w_map = --args->map_columns;
	data->h_map = --args->map_rows;
	data->increase = 32;
	data->flag = 0;
	data->door = malloc(sizeof(t_door));
	data->ply = malloc(sizeof(t_player));
	data->ray = malloc(sizeof(t_ray));
	data->mlx = malloc(sizeof(t_mlx));
	data->mlx->mlx = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->mlx, S_W, S_H, "Cub3D");
	data->mlx->img = mlx_new_image(data->mlx->mlx, S_W, S_H);
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, \
		&data->mlx->bits_per_pixel, \
		&data->mlx->line_length, \
		&data->mlx->endian);
	data->state = LOBBY;
	init_player(data->ply, data);
	init_ray(data->ray);
	init_doors(data, data->door);
	load_all_textures(data);
}

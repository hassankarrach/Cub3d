/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:16:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/24 23:36:37 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_texture(t_data *data, t_player *ply,
		t_texture **ply_textures)
{
	ply->current_frame = 0;
	ply->total_frames = 24;
	ply->last_update_time = 0;
}

void	init_player(t_player *player, t_data *data)
{
	get_x_y_player(data);
	player->posX = data->index_x * TILE_SIZE + TILE_SIZE / 2;
	player->posY = data->index_y * TILE_SIZE + TILE_SIZE / 2;
	player->fov_rd = 60 * DEG_TO_RAD;
	player->walk_direction = 0;
	player->turn_direction = 0;
	data->ply->move_speed = 1;
	data->ply->bobbing_speed = 1;
	data->ply->bobbing_amplitude = 1;
	get_angle(data);
	init_player_texture(data, data->ply, data->textures.player);
}

void	init_ray(t_ray *ray)
{
	ray->ray_ngl = 0;
	ray->hit_door = 0;
	ray->skip_door = 0;
	ray->distance = 0;
}

static void	init_sounds(t_data *data)
{
	int	i;

	i = 0;
	data->sounds[0].file_path = LOBBY_SOUND_PATH;
	data->sounds[1].file_path = AMBIENCE_SOUND_PATH;
	data->sounds[2].file_path = PSST_SOUND_PATH;
	data->sounds[3].file_path = WALKING_SOUND_PATH;
	data->sounds[4].file_path = YOU_DEAD_SOUND_PATH;
	while (i < 5)
		data->sounds[i++].is_playing = 0;
	i = 0;
	while (i < 5)
		data->sounds[i++].pid = 0;
}

t_texture	*texture_loader(t_data *data, char *texture_path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		ft_error("Memory allocation failed");
	texture->img = mlx_xpm_file_to_image(data->mlx->mlx, texture_path,
			&texture->width, &texture->height);
	if (!texture->img)
		ft_error("Texture loading failed");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (texture);
}

void	load_door_textures(t_data *data)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 1;
	while (i <= 26)
	{
		full_path = ft_strjoin("./assets/textures/doors/door_", ft_itoa(i));
		tmp = full_path;
		full_path = ft_strjoin(full_path, ".xpm");
		data->textures.door[i - 1] = texture_loader(data, full_path);
		free(tmp);
		free(full_path);
		i++;
	}
}

void	load_frame_textures(t_data *data)
{
	data->textures.frame_13.frame_red = texture_loader(data, \
		"./assets/textures/frames/wallFrame_1_red.xpm");
	data->textures.frame_13.frame_green = texture_loader(data, \
		"./assets/textures/frames/wallFrame_1_green.xpm");
	data->textures.frame_13.frame_blue = texture_loader(data, \
		"./assets/textures/frames/wallFrame_1_blue.xpm");
	data->textures.frame_13.frame_orange = texture_loader(data, \
		"./assets/textures/frames/wallFrame_1_orange.xpm");
	data->textures.frame_doors.frame_red = texture_loader(data, \
		"./assets/textures/frames/wallFrame_2_red.xpm");
	data->textures.frame_doors.frame_green = texture_loader(data, \
		"./assets/textures/frames/wallFrame_2_green.xpm");
	data->textures.frame_doors.frame_blue = texture_loader(data, \
		"./assets/textures/frames/wallFrame_2_blue.xpm");
	data->textures.frame_doors.frame_orange = texture_loader(data, \
		"./assets/textures/frames/wallFrame_2_orange.xpm");
}

static void	load_player_textures(t_data *data)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 1;
	while (i <= 24)
	{
		full_path = ft_strjoin("./assets/player/player_", ft_itoa(i));
		tmp = full_path;
		full_path = ft_strjoin(full_path, ".xpm");
		data->textures.player[i - 1] = texture_loader(data, full_path);
		free(tmp);
		free(full_path);
		i++;
	}
}

void	load_wall_textures(t_data *data)
{
	data->textures.wall_EA = texture_loader(data, data->args->East_texture);
	data->textures.wall_NO = texture_loader(data, data->args->North_texture);
	data->textures.wall_SO = texture_loader(data, data->args->South_texture);
	data->textures.wall_WE = texture_loader(data, data->args->West_texture);
}

void	load_all_textures(t_data *data)
{
	data->textures.mini_map = texture_loader(data, "./assets/mini_map.xpm");
	data->textures.icon_player = texture_loader(data, \
		"./assets/player_icon.xpm");
	data->textures.logo = texture_loader(data, "./assets/logo.xpm");
	data->textures.press_to_start = texture_loader(data, \
		"./assets/press_space.xpm");
	data->textures.you_died = texture_loader(data, "./assets/you_died.xpm");
	load_wall_textures(data);
	load_door_textures(data);
	load_player_textures(data);
}

void	init_doors(t_data *data, t_door *door, t_texture **door_textures)
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
	data->args = args;
	data->map2d = args->map_lines;
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
	load_door_textures(data);
	init_ray(data->ray);
	init_player(data->ply, data);
	init_sounds(data);
	init_doors(data, data->door, data->textures.door);
	load_frame_textures(data);
	load_all_textures(data);
}

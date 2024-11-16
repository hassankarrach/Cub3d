/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:18:23 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/15 22:23:27 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_door_textures(t_data *data)
{
	int		i;
	char	*full_path;
	char	*tmp;
	char	*texture_id;

	i = 1;
	while (i <= 26)
	{
		texture_id = ft_itoa(i);
		full_path = ft_strjoin("./assets/textures/doors/door_", texture_id);
		free(texture_id);
		tmp = full_path;
		full_path = ft_strjoin(full_path, ".xpm");
		data->textures.door[i - 1] = texture_loader(data, full_path);
		free(tmp);
		free(full_path);
		i++;
	}
}

t_texture	*texture_loader(t_data *data, char *texture_path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		ft_error(data->args, "Memory allocation failed", 1, 1);
	texture->img = mlx_xpm_file_to_image(data->mlx->mlx, texture_path,
			&texture->width, &texture->height);
	if (!texture->img)
		ft_error(data->args, "Memory allocation failed", 1, 1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (texture);
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

void	load_wall_textures(t_data *data)
{
	data->textures.wall_ea = texture_loader(data, data->args->east_texture);
	data->textures.wall_no = texture_loader(data, data->args->north_texture);
	data->textures.wall_so = texture_loader(data, data->args->south_texture);
	data->textures.wall_we = texture_loader(data, data->args->west_texture);
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

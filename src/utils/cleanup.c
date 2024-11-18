/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:05:57 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/18 05:40:02 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"


void	helper_clean(t_data *data)
{
	free_texture(data->mlx, data->textures.wall_ea);
	free_texture(data->mlx, data->textures.wall_no);
	free_texture(data->mlx, data->textures.wall_so);
	free_texture(data->mlx, data->textures.wall_we);
	free_texture(data->mlx, data->textures.mini_map);
	free_texture(data->mlx, data->textures.icon_player);
	free_texture(data->mlx, data->textures.logo);
	free_texture(data->mlx, data->textures.press_to_start);
	free_texture(data->mlx, data->textures.you_died);
	free_texture(data->mlx, data->textures.frame_13.frame_red);
	free_texture(data->mlx, data->textures.frame_13.frame_green);
	free_texture(data->mlx, data->textures.frame_13.frame_blue);
	free_texture(data->mlx, data->textures.frame_13.frame_orange);
	free_texture(data->mlx, data->textures.frame_doors.frame_red);
	free_texture(data->mlx, data->textures.frame_doors.frame_green);
	free_texture(data->mlx, data->textures.frame_doors.frame_blue);
	free_texture(data->mlx, data->textures.frame_doors.frame_orange);	
	free(data->door);
	free(data->ply);
	free(data->ray);
	free_mlx(data->mlx);
	freer(data->args);
}

void free_door_list(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		free(data->args->doors[i]);
		i++;
	}
	free(data->args->doors);
}

void free_wall_frames(t_data *data)
{
	int	i;

	i = 0;
	while (data->args->frames[i])
	{
		free(data->args->frames[i]);
		i++;
	}
	free(data->args->frames);
}

void	clean_resources(t_data *data)
{
	int	i;

	i = 0;
	printf("Cleaning resources...\n");
	free_door_list(data);
	free_wall_frames(data);
	while (i < 24)
	{
		free_texture(data->mlx, data->textures.player[i]);
		i++;
	}
	i = 0;
	while (i < 26)
	{
		free_texture(data->mlx, data->textures.door[i]);
		i++;
	}
	helper_clean(data);
}

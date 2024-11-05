/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:05:57 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/05 23:16:24 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	freer(t_args *args)
{
	char	**lines;
	int		i;

	lines = args->file_lines;
	free(args->East_texture);
	free(args->South_texture);
	free(args->West_texture);
	free(args->North_texture);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	ft_error(t_args *args, char *error_msg, bool should_exit, bool should_free)
{
	write(2, "ERROR: ", 7);
	printf("%s\n", error_msg);
	if (should_free)
		freer(args);
	if (should_exit)
		exit(1);
	return (0);
}

void	free_mlx(t_mlx *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	mlx_destroy_display(ptr->mlx);
	free(ptr->mlx);
}

void	free_texture(t_mlx *mlx, t_texture *texture)
{
	if (texture)
	{
		mlx_destroy_image(mlx->mlx, texture->img);
		free(texture);
	}
}

void	clean_resources(t_data *data)
{
	int	i;

	i = 0;
	while (i < 26)
		free_texture(data->mlx, data->textures.door[i++]);
	i = 0;
	while (i < 24)
		free_texture(data->mlx, data->textures.player[i++]);
	free_texture(data->mlx, data->textures.wall_EA);
	free_texture(data->mlx, data->textures.wall_NO);
	free_texture(data->mlx, data->textures.wall_SO);
	free_texture(data->mlx, data->textures.wall_WE);
	free_texture(data->mlx, data->textures.mini_map);
	free_texture(data->mlx, data->textures.icon_player);
	free_texture(data->mlx, data->textures.logo);
	free_texture(data->mlx, data->textures.press_to_start);
	free_texture(data->mlx, data->textures.you_died);
	free(data->door);
	free(data->ply);
	free(data->ray);
	free_mlx(data->mlx);
}

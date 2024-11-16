/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:05:57 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/16 01:26:27 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	freer(t_args *args)
{
	char	**lines;
	int		i;

	lines = args->file_lines;
	free(args->east_texture);
	free(args->south_texture);
	free(args->west_texture);
	free(args->north_texture);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	if (lines)
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
	{
		free_texture(data->mlx, data->textures.door[i]);
		i++;
	}
	i = 0;
	while (i < 24)
		free_texture(data->mlx, data->textures.player[i++]);
	free_texture(data->mlx, data->textures.wall_ea);
	free_texture(data->mlx, data->textures.wall_no);
	free_texture(data->mlx, data->textures.wall_so);
	free_texture(data->mlx, data->textures.wall_we);
	free_texture(data->mlx, data->textures.mini_map);
	free_texture(data->mlx, data->textures.icon_player);
	free_texture(data->mlx, data->textures.logo);
	free_texture(data->mlx, data->textures.press_to_start);
	free_texture(data->mlx, data->textures.you_died);
	free(data->door);
	free(data->ply);
	free(data->ray);
	free_mlx(data->mlx);
	freer(data->args);
}

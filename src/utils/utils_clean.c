/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 03:50:28 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/19 03:50:29 by hkarrach         ###   ########.fr       */
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
	free(ptr);
}

void	free_texture(t_mlx *mlx, t_texture *texture)
{
	if (texture)
	{
		mlx_destroy_image(mlx->mlx, texture->img);
		free(texture);
	}
}

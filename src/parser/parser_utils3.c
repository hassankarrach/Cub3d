/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:54:33 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/18 06:21:14 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	init_door(t_args *cub_args, int doors_count, int i, int j)
{
	cub_args->doors[doors_count] = malloc(sizeof(t_wall_door));
	cub_args->doors[doors_count]->i = j;
	cub_args->doors[doors_count]->j = i;
}

void	add_doors(t_args *cub_args)
{
	int	i;
	int	j;
	int	doors_count;

	i = 0;
	doors_count = 0;
	cub_args->doors = malloc(sizeof(t_wall_door *) * 4);
	while (i < 4)
		cub_args->doors[i++] = NULL;
	i = 0;
	while (cub_args->map2d[i] && doors_count < 3)
	{
		j = 0;
		while (cub_args->map2d[i][j] && doors_count < 3)
		{
			if (cub_args->map2d[i][j] == 'D')
			{
				init_door(cub_args, doors_count, i, j);
				doors_count++;
			}
			j++;
		}
		i++;
	}
}

void	add_wall_frames(t_args *cub_args)
{
	int	frames_per_row;
	int	i;
	int	j;

	cub_args->number_of_frames = 0;
	i = 0;
	frames_per_row = 2;
	while (cub_args->map2d[i])
	{
		j = 0;
		frames_per_row = 2;
		while (cub_args->map2d[i][j])
		{
			if (cub_args->map2d[i][j] == '1' && frames_per_row && i != 0
				&& is_logic_frame(cub_args, i, j) && j != 0
				&& j < cub_args->map_columns && i < (cub_args->map_rows - 1))
			{
				cub_args->map2d[i][j] = 'F';
				cub_args->number_of_frames++;
				frames_per_row--;
			}
			j++;
		}
		i++;
	}
}

char	*fill_extra(char *line, int max_len)
{
	int		curr_line_len;
	char	*tmp;
	char	*res;

	curr_line_len = ft_strlen(line);
	res = ft_strdup(line);
	while (max_len > (curr_line_len))
	{
		tmp = ft_strjoin(res, "X");
		free(res);
		res = tmp;
		curr_line_len++;
	}
	free(line);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 04:24:31 by kait-baa          #+#    #+#             */
/*   Updated: 2024/10/23 01:11:51 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/renderer.h"

t_wallFrame	*get_currect_texture(t_wallFrame **wall_frame, int i, int j)
{
	int	n;

	n = 0;
	while (wall_frame[n] != NULL)
	{
		if (wall_frame[n]->x == i && wall_frame[n]->y == j)
			return (wall_frame[n]);
		n++;
	}
	return (NULL);
}

static t_texture	*selected_texture_frames(e_Direction direction,
											t_frames texture_frame)
{
	if (direction == TOP)
		return (texture_frame.frame_blue);
	else if (direction == BOTTOM)
		return (texture_frame.frame_red);
	else if (direction == LEFT)
		return (texture_frame.frame_orange);
	else if (direction == RIGHT)
		return (texture_frame.frame_green);
	return (NULL);
}

t_texture	*get_wall_frame(t_data data, e_Direction direction,
		t_texture *texture_wall)
{
	t_wallFrame	*wall_frame;
	t_textures	textures;
	int			i;
	int			j;

	textures = data.textures;
	i = (int)(data.ray->min_inter.xintercept / TILE_SIZE);
	j = (int)(data.ray->min_inter.yintercept / TILE_SIZE);
	if (i >= data.w_map || j >= data.h_map || i < 0 || j < 0)
		return (NULL);
	wall_frame = get_currect_texture(data.args->frames, i, j);
	if (wall_frame == NULL)
		return (texture_wall);
	if (wall_frame->direction == direction)
		return (selected_texture_frames(direction, textures.frame_13));
	return (texture_wall);
}

int	check_wall_frame(t_data data)
{
	int	i;
	int	j;

	i = data.ray->min_inter.xintercept / TILE_SIZE;
	j = data.ray->min_inter.yintercept / TILE_SIZE;
	if (i >= data.w_map || j >= data.h_map || i < 0 || j < 0)
		return (0);
	if (data.map2d[j][i] == 'F')
		return (1);
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:17:56 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/08 21:17:57 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENES_H
# define SCENES_H

# include "../lib/libft/libft.h"
# include "cub3d.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data	t_data;

void					lobby(t_data *data);
void					game_pause(t_data *data);

#endif

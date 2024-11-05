/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:16:59 by hkarrach          #+#    #+#             */
/*   Updated: 2024/11/05 23:17:29 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

double	get_time_in_seconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + (time.tv_usec / 1000000.0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:11 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:21:12 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dig_count(int n)
{
	int	dig;

	dig = !n;
	while (n)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		d_count;
	char	*res;

	sign = n < 0;
	d_count = dig_count(n) + sign;
	res = (char *)malloc(sizeof(char) * (d_count + 1));
	if (!res)
		return (res);
	res[d_count] = '\0';
	if (sign)
	{
		*res = '-';
		res[--d_count] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (d_count-- - sign)
	{
		res[d_count] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

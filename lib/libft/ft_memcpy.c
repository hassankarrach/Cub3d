/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:14 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:21:58 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*buffer;
	const unsigned char	*source = src;

	buffer = dst;
	if (dst == src)
	{
		return (dst);
	}
	while (n > 0)
	{
		*buffer = *source;
		buffer++;
		source++;
		n--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:25 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:22:14 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	if (size == 0)
	{
		return (ft_strlen(src));
	}
	while (n < size - 1 && src[n])
	{
		dest[n] = src[n];
		n++;
	}
	if (n < size)
		dest[n] = '\0';
	while (src[n])
		n++;
	return (n);
}

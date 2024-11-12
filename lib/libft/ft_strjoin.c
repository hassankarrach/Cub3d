/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:22 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:22:13 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int)ft_strlen(s2);
	res = (char *)malloc(((len_s1 + len_s2) * sizeof(char)) + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len_s1);
	ft_memcpy(res + len_s1, s2, len_s2);
	res[len_s1 + len_s2] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:33 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:22:20 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		first;
	int		last;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	while (s1[first] && ft_strrchr(set, s1[first]))
		first++;
	last = ft_strlen(s1);
	while (s1[last - 1] && ft_strrchr(set, s1[last - 1]) && last > first)
		last--;
	res = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!res)
		return (NULL);
	else
		ft_strlcpy(res, &s1[first], last - first + 1);
	return (res);
}

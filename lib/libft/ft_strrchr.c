/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:31 by kait-baa          #+#    #+#             */
/*   Updated: 2024/11/10 21:22:19 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			last = ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		last = ((char *)&str[i]);
	return (last);
}

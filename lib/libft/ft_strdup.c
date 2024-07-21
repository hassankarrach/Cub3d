#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	str_len;
	size_t	i;
	char	*res;

	str_len = ft_strlen(s);
	res = (char *)malloc(str_len * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
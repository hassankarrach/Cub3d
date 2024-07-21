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
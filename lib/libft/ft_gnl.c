#include "libft.h"

static char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int)ft_strlen(s2);
	res = (char *)malloc(((len_s1 + len_s2) * sizeof(char)) + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len_s1);
	ft_memcpy(res + len_s1, s2, len_s2);
	res[len_s1 + len_s2] = '\0';
	free (s1);
	return (res);
}

char	*get_next_line(int fd)
{
	int		readed;
	char	*buff;
	char	*line;

	line = NULL;
	buff = malloc(2 * sizeof(char));
	if (!buff)
		return (0);
	buff[1] = '\0';
	readed = read(fd, buff, 1);
	while (readed > 0)
	{
		if (buff[0] == '\n')
        {
            line = ft_gnl_strjoin(line, buff);
			break ;
        }
		line = ft_gnl_strjoin(line, buff);
		readed = read(fd, buff, 1);
	}
	free(buff);
	return (line);
}

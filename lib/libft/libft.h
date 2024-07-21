#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>


char	*ft_strrchr(const char *str, int c);
int     ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t elements_count, size_t element_size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
//gnl
char	*get_next_line(int fd);

# endif
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 4

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char		*uchar_src = (unsigned char *)src;
	unsigned char			*uchar_dst;
	size_t					i;

	uchar_dst = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		uchar_dst[i] = uchar_src[i];
		i++;
	}
	return (dst);
}

size_t	ft_strclen_s(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	const char	chr = (char)c;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == chr)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*ft_strcdup(const char *s1, int c)
{
	size_t	len;
	char	*dest;

	if (ft_strchr(s1, c))
	{
		len = ft_strclen_s(s1, c);
		dest = malloc(sizeof(char) * (len + 2));
		if (dest == NULL)
			return (NULL);
		dest[len + 1] = '\0';
		ft_memcpy(dest, s1, len + 1);
	}
	else
	{
		len = ft_strclen_s(s1, '\0');
		dest = malloc(sizeof(char) * (len + 1));
		if (dest == NULL)
			return (NULL);
		dest[len] = '\0';
		ft_memcpy(dest, s1, len);
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
		return (ft_strcdup(s2, '\0'));
	if (s2 == NULL)
		return (NULL);
	s1_len = ft_strclen_s(s1, '\0');
	s2_len = ft_strclen_s(s2, '\0');
	dest = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[s1_len + s2_len] = '\0';
	ft_memcpy(dest, s1, s1_len);
	ft_memcpy(dest + s1_len, s2, s2_len);
	return (dest);
}

#include <stdio.h>
char *get_next_line(int fd)
{
	char		*line;
	static char	*memo;
	char		*buf;
	ssize_t		read_return;

	buf = malloc(BUFFER_SIZE + 1);
	if (memo != NULL && memo[0] == '\0')
		return (NULL);
	if (ft_strchr(memo, '\n') != 0)
	{
//		puts("\\n in memo");
		line = ft_strcdup(memo, '\n');
		memo = ft_strcdup(memo + ft_strclen_s(line, '\n') + 1, '\0');
//		printf("line -> %s\nmemo -> %s\n|", line, memo);
		return (line);
	}
//	puts("\\n not in memo");
	while (ft_strchr(memo, '\n') == 0)
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		buf[read_return] = '\0';
		memo = ft_strjoin(memo, buf);
//		printf("buf -> %s%%memo -> %s%%\n", buf,  memo);
		if (read_return < BUFFER_SIZE)
		{
			line = ft_strcdup(memo, '\n');
			memo = ft_strcdup("", '\0');
//			printf("==before_return1==\nmemo -> %s%%\nline -> %s%%\n", memo, line);
			return (line);
		}
	}
	line = ft_strcdup(memo, '\n');
	memo = ft_strcdup(memo + ft_strclen_s(line, '\n') + 1, '\0');
//	printf("==before_return2==\nmemo -> %s%%\nline -> %s%%\n", memo, line);
	return (line);
}

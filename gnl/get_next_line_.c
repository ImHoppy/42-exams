#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

int	ft_strlen(char *s)
{
	int n;

	if (!s)
		return (0);
	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	ft_len_eol(char *s)
{
	int n;

	if (!s)
		return (0);
	n = 0;
	while (s[n])
	{
		if (s[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

char	*ft_strncpy(char *dst, const char *src, int size)
{
	int i;

	if (!src || !dst)
		return (dst);
	for (i = 0; i < size && src[i];i++)
		dst[i] = src[i];
	dst[i] = '\0';
	for (; i < size; i++)
		dst[i] = '\0';
	return (dst);
}

char	*ft_join(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*new;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((new = malloc(sizeof(char) * (len1 + len2 + 1))) == NULL)
		return (NULL);
	ft_strncpy(new, s1, len1);
	ft_strncpy(new+len1, s2, len2);
	if (s1)
		free(s1);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE+1];
	char		*line;
	char		*tmp;
	int			readed;
	int			len_b;
	int			len_n;

	line = NULL;
	len_b = ft_strlen(buffer);
	while ((readed = read(fd, buffer+len_b, BUFFER_SIZE-len_b)) > 0 || buffer[0] != '\0')
	{
		buffer[readed+len_b] = '\0';
		len_n = ft_len_eol(buffer);
		if (len_n == -1)
		{
			len_b = 0;
			line = ft_join(line, buffer);
		}
		else
		{
			tmp = malloc(sizeof(char) * len_n + 2);
			ft_strncpy(tmp, buffer, len_n + 1);
			line = ft_join(line, tmp);
			free(tmp);
			ft_strncpy(buffer, buffer+len_n + 1, BUFFER_SIZE-len_n-1);
			return (line);
		}
	}
	return (line);
}

int main()
{
	char *line = NULL;
	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}

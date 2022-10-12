#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int ft_strlen(char *s)
{
	int n=0;
	if(!s)
		return (n);
	while (s[n])
		n++;
	return (n);
}
int ft_eol(char *s)
{
	int n=0;
	if(!s)
		return (n);
	while (s[n])
	{
		if (s[n] == '\n')
			return (n+1);
		n++;
	}
	return (-1);
}

char	*ft_strncpy(char *dst, const char *src, int size)
{
	int i;
	
	for (i=0;i<size && src[i];i++)
		dst[i] = src[i];
	dst[i] = '\0';
	for (;i<size;i++)
		dst[i] = '\0';
	return (dst);
}

char	*strjoin(char *s1, char *s2)
{
	char *line;
	int s1l, s2l;
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	if ((line = malloc(sizeof(char) * (s1l + s2l +1))) == NULL)
		return (NULL);
	ft_strncpy(line, s1, s1l);
	ft_strncpy(line+s1l, s2, s2l);
	if (s1)
		free(s1);
	s1 = line;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE+1];
	char		*line;
	char		*tmp;
	int			blen;
	int			nlen;
	int			readed;

	line = NULL;
	blen = ft_strlen(buffer);
	while ((readed = read(fd, buffer+blen, BUFFER_SIZE-blen)) > 0 || buffer[0] != '\0')
	{
		buffer[readed+blen] = '\0';
		blen = 0;
		nlen = ft_eol(buffer);
		if (nlen == -1)
			line = strjoin(line, buffer);
		else
		{
			if ((tmp = malloc(sizeof(char) *(nlen + 1))) == NULL)
				return (NULL);
			ft_strncpy(tmp, buffer, nlen);
			line = strjoin(line, tmp);
			free(tmp);
			ft_strncpy(buffer, buffer+nlen, BUFFER_SIZE-nlen);
			return (line);
		}
	}
	return (line);
}
/*
#include <stdio.h>
int main()
{
	char *line;

	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
*/

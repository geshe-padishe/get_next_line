#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

static void ft_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
}

static void ft_bzero(char *str, int size)
{
	while (size-- > 0)
	{
		*str = 0;
		str++;
	}
}

int ft_strlen(str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char *ft_realloc(char *str, int size)
{
	char *new_str;
	int i;

	if((new_str = malloc(size + ft_strlen(str))) == NULL)
		return (NULL);
	ft_bzero(new_str, size);
	ft_strcat(new_str, str);
	free(str);
	return (new_str);
}

int ft_len_before_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int has_nw(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}


char *clean_str(char *str, len)
{
	char *new_str;

	str += len;
}

int get_next_line(int fd, char **s)
{
	char buff[BUFF_SIZE + 1];
	(void)s;
	int ret;
	int i;
	int len;
	static char *str = {'\0'};

	if (BUFF_SIZE <= 0)
		return (-1);
	i = 0;
	if (str[0] == '\0')
	{
		free(str);
		if((str = malloc(BUFF_SIZE)) == NULL)
			return (-1);
	}
	while (len = has_nw(str) == 0 && ret = read(fd, buff, BUFF_SIZE) > 0)
	{
		if ((str = ft_realloc(str, ret)) == NULL)
			return (-1);
		buff[ret] = '\0';
		ft_strcat(str, buff);
	}
	if (len > 0)
	{
		s = malloc(len);
		while (str[i] != '\n')
		{
			s[i] = str[i];
			i++;
		}
		s[i] = '\0';
	}
	str = clean_str(str, len);
//	while (str[i] && str[i] != '\n')
//		i++;
//	if (str[i] == '\n')
//	{
//		write(1, str, i + 1);
//		str += i + 1;
//		return (1);
//	}
//	return (0);
}

int main(int argc, char **argv)
{
	char *s;
	int fd;
	int i;

	if((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	while(get_next_line(fd, &s) != 0)
		i++;
	return (0);
}

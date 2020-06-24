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

static char *ft_realloc(char *str, int size)
{
	char *new_str;
	int i;

	if((new_str = malloc(size)) == NULL)
		return (NULL);
	ft_bzero(new_str, size);
	ft_strcat(new_str, str);
	free(str);
	return (new_str);
}

int get_next_line(int fd, char **s)
{
	char buff[BUFF_SIZE + 1];
	(void)s;
	int ret;
	int row;
	static char *str;
	
	row = BUFF_SIZE;
	if((str = malloc(BUFF_SIZE)) == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		row += ret;
		if ((str = ft_realloc(str, row)) == NULL)
			return (-1);
		buff[ret] = '\0';
		ft_strcat(str, buff);
		if (ret < BUFF_SIZE)
			break;
	}
	printf("%s", str);
	return (0);
}

int main(int argc, char **argv)
{
	char *s;
	int fd;

	if((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	get_next_line(fd, &s);
	get_next_line(fd, &s);
//	while (get_next_line(fd, &s))
//	{
//		printf("%s\n", s);
//		free(s);
//	}
	return (0);
}

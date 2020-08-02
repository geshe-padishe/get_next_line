#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

int ft_nl_index(char *str)
{
	int i;

	if (str == NULL)
		str = malloc(BUFF_SIZE + 1);
	else
	{
		i = -1;
		while (str[++i])
			if (str[i] == '\n')
				return (i);
	}
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_send_clean(char *s, char *str, int nl_index)
{
	int i;
	char *new_str;

	s = malloc(nl_index + 1);
	new_str = malloc(ft_strlen(str) - nl_index + 1);
	                                                           //si nl_index = 0?
	while (i < nl_index)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	while (str[nl_index + i])
	{
		new_str[i] = str[nl_index + i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

char *ft_catfree(char *str, char *buff)
{
	char *new_str;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	if (str == NULL)
	{
		len = ft_strlen(buff);
		new_str = malloc(len + 1);
	}
	else
	{
		len = ft_strlen(str) + ft_strlen(buff);
		new_str = malloc(len + 1);
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
	}
	while (buff[j])
	{
		new_str[i] = buff[j];
		j++;
		i++;
	}
	new_str[i] = '\0';
	if (str != NULL)
		free(str);
	str = NULL;
	return (new_str);
}

int get_next_line(int fd, char **line)
{
	int nl_index;
	char buff[BUFF_SIZE + 1];
	static char *str;

	if ((nl_index = ft_nl_index(str)) > 0)
		str = ft_send_clean(line[0], str, nl_index);
	else
	{
		while (read(fd, buff, BUFF_SIZE) > 0 && (nl_index = ft_nl_index(str)) == 0)
			str = ft_catfree(str, buff);
		if (nl_index == 0)
		{
			str = ft_send_clean(line[0], str, ft_strlen(str));
			free(str);
			str = NULL;
			return (0);
		}
		else
			str = ft_send_clean(line[0], str, nl_index);
	}
	return (1);
}

int main()
{
	char *s;
	int fd;
	int i;

	if ((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &s) != 0)
		printf("%s\n", s);
	return (0);
}

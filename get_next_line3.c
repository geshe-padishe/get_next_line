#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

char *ft_nl_index(char *str, int *nl_index)
{
	int i;

	i = 0;
	if (str == NULL)
	{
		str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		while (i <= BUFF_SIZE)
			str[i++] = '\0';
	}
	else
		while (str[i])
			if (str[i++] == '\n')
				*nl_index = i - 1;
	return (str);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_send_clean(char **s, char *str, int nl_index)
{
	int i;
	char *new_str = NULL;

	i = 0;
	*s = (char*)malloc(sizeof(char) * (nl_index + 1));
	while (i < nl_index)
	{
		(*s)[i] = str[i];
		i++;
	}
	(*s)[i] = '\0';
	i = 0;
	if (nl_index != ft_strlen(str))
	{
		new_str = (char*)malloc(sizeof(char) * (ft_strlen(str) - nl_index + 1));
		while (str[nl_index + i + 1])
		{
			new_str[i] = str[nl_index + i + 1];
			i++;
		}
		new_str[i] = '\0';
	}
	free(str);
	if (nl_index != ft_strlen(str))
		return (new_str);
	return (NULL);
}

char *ft_catfree(char *str, char *buff, int len)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;
	buff[len] = '\0';
	len = ft_strlen(str) + ft_strlen(buff);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (buff[j])
	{
		new_str[i] = buff[j];
		j++;
		i++;
	}
	free(str);
	return (new_str);
}

int get_next_line(int fd, char **line)
{
	int nl_index;
	char buff[BUFF_SIZE + 1];
	static char *str = NULL;
	int len;

	str = ft_nl_index(str, &nl_index);
	if (nl_index > 0)
		str = ft_send_clean(line, str, nl_index);
	else
	{
		while ((str = ft_nl_index(str, &nl_index)) == 0 && (len = read(fd, buff, BUFF_SIZE)) > 0)
			str = ft_catfree(str, buff, len);
		if (len == 0)
		{
			str = ft_send_clean(line, str, ft_strlen(str));
			free(str);
			str = NULL;
			return (0);
		}
		else
			str = ft_send_clean(line, str, nl_index);
	}
	return (1);
}

int main()
{
	char **s = NULL;
	int fd;

	if ((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, s) != 0)
		printf("%s\n", s[0]);
	return (0);
}


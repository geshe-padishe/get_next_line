#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

int ft_nl_index(char *str)
{
	int i;

	i = -1;
	if (str == NULL)
	{
		str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		while (++i <= BUFF_SIZE)
			str[i] = '\0';
	}
	else
		while (str[++i])
			if (str[i] == '\n')
				return (i);
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char *ft_send_clean(char *s, char *str, int nl_index)
{
	int i;
	char *new_str = NULL;

	i = 0;
	s = (char*)malloc(sizeof(char) * (nl_index + 1));
	while (i < nl_index)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	i = 0;
	//new_str = (char*)malloc(sizeof(char)*(ft_strlen(str) - nl_index + 1));
	if (nl_index != ft_strlen(str))
	{
		new_str = (char*)malloc(sizeof(char)*(ft_strlen(str) - nl_index + 1));
		while (str[nl_index + i])
		{
			new_str[i] = str[nl_index + i];
			i++;
		}
		new_str[i] = '\0';
	}
	printf("str: %p\n",str);
	free(str);
	str = NULL;
	//printf("new_str: %s | nl_index : %i | str : %s", new_str, nl_index, str);
	if (nl_index != ft_strlen(str))
		return (new_str);
	else
		return (NULL);
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
		printf("%i\n", len);
		new_str = malloc(len + 1);
	}
	else
	{
		len = ft_strlen(str) + ft_strlen(buff);
		new_str = (char *)malloc(sizeof(char) * (len + 1));
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
	}
	//printf("cat free1\n");
	while (buff[j])
	{
		//printf("while catfree\n");
		new_str[i] = buff[j];
		j++;
		i++;
	}
	new_str[i] = '\0';
	//printf("new_str : --%s--\n", new_str);
	//if (str != NULL)
	//	free(str);
	//str = NULL;
	return (new_str);
}

int get_next_line(int fd, char **line)
{
	int nl_index;
	char *buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	static char *str = NULL;
	
	int	len = 0;

	if ((nl_index = ft_nl_index(str)) > 0)
	{
		//printf("wewe\n");
		str = ft_send_clean(line[0], str, nl_index);
	}
	else
	{
		//printf("fd : %i | str: %s]\n", fd, str);
		while ((len = read(fd, buff, BUFF_SIZE)) > 0 && (nl_index = ft_nl_index(str)) == 0)
		{
			buff[len] = '\0';
		//	printf("buff: %s | nl_index : %i\n", buff, nl_index);
			str = ft_catfree(str, buff);
		}
		if ((nl_index = ft_nl_index(str)) == 0)
		{
	printf("aaaaa\n");
	printf("str: %p\n",str);
			str = ft_send_clean(line[0], str, ft_strlen(str));
			free(str);
	printf("2aaaaa\n");
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
	char *s = NULL;
	int fd;
	
	if ((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &s) != 0)
		printf("%s\n", s);
	return (0);
}

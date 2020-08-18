/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:17:46 by ngenadie          #+#    #+#             */
/*   Updated: 2020/08/18 21:01:35 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

int		ft_nl_index(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_send_clean(char **s, char *str, int nl_index)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	*s = (char*)malloc(sizeof(char) * (nl_index + 1));
	while (i < nl_index - 1 && (*s)[i] != '\n')
	{
		(*s)[i] = str[i];
		i++;
	}
	(*s)[i] = '\0';
	i = 0;
	if (nl_index + 1 != ft_strlen(str))
	{
		new_str = (char*)malloc(sizeof(char) * (ft_strlen(str) - nl_index + 1));
		while (str[nl_index + ++i + 1])
			new_str[i] = str[nl_index + i + 1];
		new_str[i] = '\0';
	}
	free(str);
	str = NULL;
	return (new_str);
}

char	*ft_realloc(char *str, char *buff, int len)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff[len] = '\0';
	len = ft_strlen(str) + ft_strlen(buff);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	//not secured
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
	new_str[i] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

int		get_next_line(int fd, char **line)
{
	int			nl_index;
	char		buff[BUFFER_SIZE + 1];
	static char	*str = NULL;
	int			len;

	if ((!str && !(str = malloc(sizeof(char) * (BUFFER_SIZE + 1)))
		&& (str[0] = 0) ) || BUFFER_SIZE <= 0)
		return (-1);
	while ((nl_index = ft_nl_index(str)) == 0 &&
			(len = read(fd, buff, BUFFER_SIZE)) > 0)
		if (!(str = ft_realloc(str, buff, len)))
			return (-1);
	if ((nl_index = ft_nl_index(str)) == 0 || nl_index + 1 == ft_strlen(str))
	{
		str = ft_send_clean(line, str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	else
		str = ft_send_clean(line, str, nl_index);
	//printf("str: %s\nnl_index: %i\nbuff:%s", str, nl_index, buff);
	if (len == 0)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	char *s = NULL;
	int fd;
	(void)ac;
	int n = 10;
	int ret;
	(void)n;
	(void)av;

	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &s)) != 0)
	{
		printf("line: %s\n", s);
		free(s);
		s = NULL;
	}
	//printf("line: %s\n", s);
	//	system("leaks a.out");
	return (0);
}

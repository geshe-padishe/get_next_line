#include <string.h>
#include <stdio.h>

int ft_nl_index(str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (0);
}

char *ft_send_&_clean(char *s, char *str, int nl_index)
{
	int i;
	char *s;

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
	return (new_str);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_catfree(char *str, char *buff)
{
	char *new_str;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(str) + ft_strlen(buff);
	new_str = malloc(len + 1);
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
	free(buff);
	return (new_str);
}

int get_next_line(int fd, char **line)
{
	int nl_index;
	static char *str = {'\0'};
	char buff[BUFF_SIZE + 1];

	if ((nl_index = ft_nl_index(str)) > 0)
		str = ft_send_&_clean(line[0], str, nl_index);
	else
		while (read(fd, buff, BUFF_SIZE) > 0 && (nl_index = ft_nl_index(str)) == 0)
			str = ft_catfree(str, buff);
	if (nl_index == 0)
	{
		str = ft_send_&_clean(line[0], str, ft_strlen(str));
		free(str);
	}
	else
		str = ft_send_&_clean(line[0], str, nl_index);
}

int main()
{
	if ((fd = open("PAGE", O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &s) != 0)
		i++;
	return (0);
}

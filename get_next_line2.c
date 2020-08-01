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

char *ft_realcat(char *str, char *buff)
{
	int i;

	i = 0;
	new_str = malloc(ft_strlen(str) + ft_strlen(buff) + 1);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	while (*buff)
	{
		new_str[i] = buff;
		buff++;
	}
	free(buff);
	return (new_str);
}

int get_next_line(int fd, char **line)
{
	int i;
	int nl_index;
	char *buff;
	static char str = {'\0'};

	i = 0;
	if ((nl_index = ft_nl_index(str)) > 0)
	{
		ft_send_&_clean(line, str, nl_index);
		return (1);
	}
	nl_index = 0;
	else
		while (read(fd, buff, BUFF_SIZE) > 0 && (nl_index = ft_nl_index(str)) == 0)
			str = ft_realcat(str, buff);
	if (nl_index == 0)
	{
		if (str[0] = '\0')
			return (0);
		else
		{
			while (str[i])
			{
				line[i] = str[i];
				i++;
			}
			free(str);
			free(buff);
			return (1);
		}
	}
	else
	{
		ft_send_&_clean(line, str, nl_index);
		return (1);
	}
}

int main()
{

}

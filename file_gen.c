#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

int		main(int ac, char **av)
{
	char	*content;
	int		prob;
	int		len;
	int		fd;

	srand(time(0));
	if (ac < 3)
	{
		printf("Fuck off\n");
		return (1);
	}
	fd = open(av[1], O_CREAT | O_WRONLY);
	len = rand() % atoi(av[2]);
	prob = atoi(av[3]);
	if (!(content = (char*)malloc(sizeof(char) * len)))
		return (1);
	for (int i = 0; i < len; i++)
	{
		if (rand() % prob == 0)
			content[i] = '\n';
		while (!isprint(content[i]))
			content[i] = rand() % 127;
	}
	write(fd, content, (size_t)len);
	return (0);
}

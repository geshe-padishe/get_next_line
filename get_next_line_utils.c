#include "get_next_line.h"

int	get_next_line2(char **str, char ***line, int nl_index, int len)
{
	if (len < 0)
		return (-1);
	if ((nl_index = ft_nl_index(*str)) == 0 || nl_index == ft_strlen(*str))
	{
		if (!(*str = ft_send_clean(*line, *str, ft_strlen(*str))))
			return (-1);
		free(*str);
		*str = NULL;
	}
	else if (!(*str = ft_send_clean(*line, *str, nl_index)))
		return (-1);
	if (len == 0 && *str == NULL)
		return (0);
	return (1);
}

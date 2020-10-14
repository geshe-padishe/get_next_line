#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFF_SIZE
#  define BUFF_SIZE 1
# endif

int get_next_line(int e, char **s);
int ft_nl_index(char *str);
int ft_strlen(char *str);
char *ft_realloc(char *str, char *buff, int len);
char *ft_send_clean(char **s, char *str, int nl_index);
#include <stdlib.h>
#include <fcntl.h>


#endif

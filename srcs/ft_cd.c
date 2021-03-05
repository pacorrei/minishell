#include "minishell.h"

void    ft_cd(char *path)
{
    char *error;

    printf("path :%s\n", path);
    if (chdir(path) == -1)
    {
		error = strerror(errno);
		ft_putstr(error);
        ft_putchar('\n');
	}
}
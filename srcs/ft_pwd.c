#include "minishell.h"

void    ft_pwd(char **envp)
{
    int i;
    int j;

    i = 0;
    while (envp[i] != NULL)
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D' && envp[i][3] == '=')
        {
            j = 4;
            while (envp[i][j] != '\0')
            {
                ft_putchar(envp[i][j]);
                j++;
            }
            ft_putchar('\n');
        }
        i++;
    }
}
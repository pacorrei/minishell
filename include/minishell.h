#ifndef MINISHELL_H
# define MINISHELL_H
#include "get_next_line.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void    ft_pwd(char **envp);
void    ft_env(char **envp);
void    ft_cd(char *path);
void	ft_putchar(char c);
void	putstr_double_char(char **str);
void	ft_putstr(char *str);

#endif
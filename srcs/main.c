#include "minishell.h"

int		count_word(char *str)
{
	int i;
	int ret;
	ret = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if(((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9')) &&
		(str[i + 1] < 'a' || str[i + 1] > 'z') &&
		(str[i + 1] < 'A' || str[i + 1] > 'Z') &&
		(str[i + 1] < 'a' || str[i + 1] > 'z'))
			ret++;
		i++;
	}
	return (ret);
}

void	get_words(char *str, char **dest)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9'))
			j++;
		if (((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9')) &&
		((str[i + 1] < 'a' || str[i + 1] > 'z') &&
		(str[i + 1] < 'A' || str[i + 1] > 'Z') &&
		(str[i + 1] < 'a' || str[i + 1] > 'z')))
		{
			dest[k] = malloc(sizeof(char) * (j + 1));
			dest[k][j] = '\0';
			k++;
			j = 0;
		}
		i++;
	}
}

void	fill_tab(char *str, char **dest)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9')) && dest[k] != NULL)
		{
			dest[k][j] = str[i];
			j++;
		}
		if (((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9')) &&
		((str[i + 1] < 'a' || str[i + 1] > 'z') &&
		(str[i + 1] < 'A' || str[i + 1] > 'Z') &&
		(str[i + 1] < 'a' || str[i + 1] > 'z')))
		{
			k++;
			j = 0;
		}
		i++;
	}
}

char	**str_to_wordtab(char *str)
{
	int ret;
	char	**dest;

	ret = count_word(str);
	dest = malloc(sizeof(char*) * (ret + 1));
	dest[ret] = NULL;
	get_words(str, dest);
	fill_tab(str, dest);
	return (dest);
}


void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	putstr_double_char(char **str)
{
	int i;
	
	i = 0;
	while (str[i] != NULL)
	{
		ft_putstr(str[i]);
		ft_putchar('\n');
		i++;
	}

}

char **get_nbr_path(char **envp, int i, char **path)
{
	int j;
	int k;
	int l;

	j = 5;
	k = 0;
	l = 0;
	while (envp[i][j] != '\0')
	{
		if (envp[i][j] == ':')
		{
			path[k] = malloc(sizeof(char) * l + 1);
			path[k][l] = '\0';
			l = 0;
			k++;
			j++;
		}
		j++;
		l++;
	}
	path[k] = malloc(sizeof(char) * l + 1);
	path[k][l] = '\0';
	return (path);
}

char **fill_path(char **envp, int i, char **path)
{
	int j;
	int k;
	int l;

	j = 5;
	k = 0;
	l = 0;
	while (envp[i][j] != '\0' && path[k] != NULL)
	{
		while (envp[i][j] != ':' && envp[i][j] != '\0' && path[k][l] != '\0')
		{
			path[k][l] = envp[i][j];
			l++;
			j++;
		}
		l = 0;
		k++;
		j++;
	}
	return (path);
}

char **get_path(char **envp, char **path)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			while (envp[i][j] != '\0')
			{
				if (envp[i][j] == ':')
					k++;
				if (envp[i][j + 1] == '\0')
				{
					k++;
					path = malloc(sizeof(char*) * (k + 1));
					path[k] = NULL;
					path = get_nbr_path(envp, i, path);
					path = fill_path(envp, i, path);
				}
				j++;
			}
		}
		i++;
	}
	return (path);
}

void	exec_cmd(char *path, char **str)
{
	pid_t	pid;
	int		status;
	char	*error;

	status = 0;
	error = NULL;
	pid = fork();
	if (pid == -1)
	{
		error = strerror(errno);
		ft_putstr(error);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, str, NULL) == -1)
		{
			error = strerror(errno);
			ft_putstr(error);
			exit(0);
		}
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_concat(char	*s1, char *s2)
{
	int i;
	int j;
	char *ret;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		i++;
		j++;
	}
	ret = malloc(sizeof(char) * (j + 1));
	ret[j] = '\0';
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		ret[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ret[j] = s2[i];
		i++;
		j++;
	}
	return (ret);
}

char	*ft_search_dir(char	*path, char	*cmd)
{
	DIR *dir;
	struct dirent *read_dir;
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	dir = opendir(path);
	if (!dir)
		return (NULL);
	while ((read_dir = readdir(dir)))
	{
		if (ft_strcmp(read_dir->d_name, cmd) == 0)
		{
			tmp = ft_concat(path, "/");
			ret = ft_concat(tmp, cmd);
			free(tmp);
		}
	}
	closedir(dir);
	return (ret);
}

int		verif_builtin(char	**str, char **envp)
{
	int i;

	i = 0;
	if (ft_strcmp(str[i], "echo") == 0)
	{
		//ft_echo(str, i);
		return (1);
	}
	if (ft_strcmp(str[i], "pwd") == 0)
	{
		ft_pwd(envp);
		return (1);
	}
	if (ft_strcmp(str[i], "env") == 0)
	{
		ft_env(envp);
		return (1);
	}
	if (ft_strcmp(str[i], "cd") == 0)
	{
		ft_cd(str[i + 1]);
		return (1);
	}
	return (0);
}

void	ft_get_cmd_path(char **path, char **str, char **envp)
{
	int i;
	int j;
	char	*path_cmd;

	j = 0;
	path_cmd = NULL;
	i = verif_builtin(str, envp);
	if (i == 1)
		return ;
	while (path[i] != NULL && path_cmd == NULL)
	{
		path_cmd = ft_search_dir(path[i], str[j]);
		i++;
	}
	exec_cmd(path_cmd, str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int		verif_quote(char *str)
{
	int i;
	int quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		if (str[i] == '\"' && quote == 0)
			quote = 2;
		else if (str[i] == '\"' && quote == 2)
			quote = 0;
		i++;
	}
	return (quote);
}

int main(int ac, char **av, char **envp)
{
	char *line;
	char **str;
	char **path;
	int ret;

	(void)ac;
	(void)av;
	line = NULL;
	path = NULL;
	ret = 0;
	path = get_path(envp, path);
	while (42)
	{
		ft_putstr("prompt>");
		get_next_line(0, &line);
		if ((ret = verif_quote(line)))
		{
			if (ret == 1)
				ft_putstr_fd("Syntax error, simple quote not closed\n", 2);
			if (ret == 2)
				ft_putstr_fd("Syntax error, double quote not closed\n", 2);
		}
		if (ret == 0)
		{
			str = str_to_wordtab(line);
			ft_get_cmd_path(path, str, envp);
		}
	}
}
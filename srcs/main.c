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
	printf("%d", ret);
	syscall;
	return (ret);
}

void	get_words(char *str, char **dest)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9'))
		{
			i++;
			j++;
		}
		dest[k] = malloc(sizeof(char) * (j + 1));
		dest[k][j] = '\0';
		k++;
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
		while ((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= '0' && str[i] <= '9'))
		{
			dest[k][j] = str[i];
			i++;
			j++;
		}
		k++;
		j = 0;
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

int main()
{
	char *line;
	char **str;
	line = NULL;
	while (42)
	{
		ft_putstr("prompt>");
		get_next_line(0, &line);
		str = str_to_wordtab(line);
		putstr_double_char(str);
	}
}
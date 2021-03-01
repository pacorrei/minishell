/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *str, int i)
{
	char *temp;

	if ((temp = ft_substr(str, i + 1, ft_strlen(str))) == NULL)
		return (NULL);
	free(str);
	return (temp);
}

int		verif_erreurs(int fd, char **line)
{
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (1);
	return (0);
}

char	*search_line(int fd, char **line, char *str)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*temp;

	if (verif_erreurs(fd, line) == 1)
		return (NULL);
	while ((verif_tab(str) == 0) && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((temp = ft_strjoin(str, buff)) == NULL)
			return (NULL);
		free(str);
		str = temp;
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

int		ft_return(int i, char **str)
{
	if ((*str)[i] == '\n')
	{
		(*str) = ft_realloc((*str), i);
		return (1);
	}
	if ((*str)[i] == '\0')
	{
		free((*str));
		(*str) = NULL;
		return (0);
	}
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char			*str = NULL;
	int					i;

	i = 0;
	if (str == NULL)
	{
		if (!(str = malloc(sizeof(char) * 1)))
			return (-1);
		str[0] = '\0';
	}
	str = search_line(fd, line, str);
	if (str == NULL)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if ((*line = ft_substr(str, 0, i)) == NULL)
		return (-1);
	return (ft_return(i, &str));
}

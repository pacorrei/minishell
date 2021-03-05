/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		verif_tab(char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	int		j;
	char	*str;

	i = 0;
	i2 = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	while (s1[i])
		i++;
	while (s2[i2])
		i2++;
	if (!(str = malloc(sizeof(char) * (i + i2 + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (i < start)
	{
		if (!(new = malloc(sizeof(char) * 1)))
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	i = 0;
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	new[len] = '\0';
	while (i < len && new[i] != '\0' && s[start] != '\0')
	{
		new[i] = s[start];
		i++;
		start++;
	}
	return (new);
}

int		ft_strlen(const char *src)
{
	int i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(*dest) * i + 1);
	dest[i] = '\0';
	i = 0;
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

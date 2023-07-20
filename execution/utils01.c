/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:09:06 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/19 16:08:04 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *str, int ch)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
	{
		if (ft_strlen(s) < len)
			len = ft_strlen(s);
		p = malloc(sizeof(char) * len + 1);
		if (!p)
			return (NULL);
		while (i < len)
			p[i++] = s[start++];
	}
	else
		p = malloc(1);
	if (!p)
		return (p);
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*p;
	int		i;

	len = ft_strlen(str);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = 0x0;
	return (p);
}

int	alpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
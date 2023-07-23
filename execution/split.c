/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:04:43 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/22 08:11:42 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calcule_mot(char const *str, char c)
{
	int	i;
	int	calcul;

	i = 0;
	calcul = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			calcul++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (calcul);
}

static int	calcule_lettre(char const *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i] != c && str[i])
	{
		j++;
		i++;
	}
	return (j);
}

static char	*ft_charge(char const *str, char c, int len)
{
	int		i;
	int		k;
	char	*p;

	i = 0;
	p = malloc(sizeof(char) * (len + 1));
	if (!p || len == 0)
		return (NULL);
	k = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i] != c && str[i])
		p[k++] = str[i++];
	p[k] = '\0';
	return (p);
}

char	**ft_free(char **p, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**p;
	int		j;
	char	*ptr;
	int		len;

	i = 0;
	p = malloc(sizeof(char *) * (calcule_mot(s, c) + 1));
	if (!p)
		return (NULL);
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		len = calcule_lettre(s + i, c);
		ptr = ft_charge(s + i, c, len);
		if (!ptr)
			return (ft_free(p, j));
		if (ptr)
			p[j++] = ptr;
		i += len;
	}
	p[j] = NULL;
	return (p);
}

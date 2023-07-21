/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:36:18 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 14:39:51 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_path(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ':')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ':')
			i++;
	}
	return (++count);
}

char	*ft(char *s, char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len && s2[i])
	{
		s[i] = s2[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

char	**ft_split_path(char *str)
{
	char	**s;
	int		i;
	int		j;
	int		a;

	s = malloc((sizeof(char *)) * (count_path(str)));
	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ':')
			i++;
		a = i;
		while (str[i] && str[i] != ':')
			i++;
		if (i > a)
			s[j++] = ft(malloc (i - a + 1), str + a, i - a);
	}
	s[j] = NULL;
	return (s);
}

int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = ft_count(n);
	p = malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	p[i--] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
	}
	while (n)
	{
		p[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (p);
}

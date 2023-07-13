/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:03:37 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/11 19:30:43 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *st1, char *st2)
{
	size_t			i;

	i = 0;
	if (st1 == NULL)
	{
		return (-1);
	}
	else if (st2 == NULL)
	{
		return (1);
	}
	while (st1[i] != '\0' || st2[i] != '\0')
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	p = (char *)malloc (ft_strlen (s1) + ft_strlen (s2) + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	**my_env(t_all *all)
{
	t_var	*p;
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = 0;
	p = all->env;
	while (p)
	{
		len++;
		p = p->next;
	}
	tmp = malloc(sizeof(char *) * (len + 1));
	i = 0;
	p = all->env;
	while (p)
	{
		tmp[i] = ft_strjoin_n(p->key, "=");
		tmp[i] = ft_strjoin(tmp[i], p->val);
		i++;
		p = p->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

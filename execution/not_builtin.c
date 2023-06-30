/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:49:15 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/30 19:51:10 by kaboussi         ###   ########.fr       */
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

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if(!s1)
		return (s2);
	if(!s2)
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
	int	i;
	int	len;
	char **tmp;

	i = 0;
	len = 0;
	p = all->exp;
	while (p)
	{
		len++;
		p = p->next;
	}
	tmp = malloc(sizeof(char *) *len+1);
	// if (!tmp)
	// 	retun (NULL);
	i = 0;
	p = all->exp;
	while (p)
	{
		tmp[i] = ft_strjoin_n(p->key , "=");
		tmp[i] = ft_strjoin(tmp[i] , p->val);
		i++;
		p = p->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ftputstr(char *str)
{
	int i;

	i =0;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
}

// char	*joinpath(t_all	*all)
// {
// 	char **path
	
// 	path = ft_split_path(key->val);
// 	i = 0;
// 	if (!strchr(p->str[0], '/'))
// 	{
// 		while (path[i])
// 		{
// 			join = ft_strjoin(path[i], "/");
// 			join = ft_strjoin(join, p->str[0]);
// 			if (access(join, R_OK) == 0)
// 				execve(join, p->str, k);
// 			i++;
// 		}
// 	}
// }

void    one_cmd_nb(t_all *all, t_simple_cmd *p)
{
	int 	i;
	char	**path;
	char	**k;
	char *join;
 	t_var	*key;

	p = all->cmd;
	i = fork();
	if (i == 0)
	{
		k = my_env(all);
		key = check_char(all->env, "PATH");
		if (key)
		{
			path = ft_split_path(key->val);
			i = 0;
			if (!strchr(p->str[0], '/'))
			{
				while (path[i])
				{
					join = ft_strjoin(path[i], "/");
					join = ft_strjoin(join, p->str[0]);
					if (access(join, R_OK) == 0)
						execve(join, p->str, k);
					i++;
				}
			}
			else
				execve(p->str[0], p->str, k);
			ftputstr("sash: ");
			ftputstr(p->str[0]);
			ftputstr(": ");
			perror("");
			exit (0);
		}
	} else {
		int stat;
		wait(&stat);
	}
	// else
		
}
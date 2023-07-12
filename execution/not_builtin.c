/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:49:15 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/06 19:30:31 by kaboussi         ###   ########.fr       */
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

void	check_path(t_var *key, char **k, t_simple_cmd *p)
{
	int		i;
	char	*join;
	char	**path;

	path = ft_split_path(key->val);
	if (!strchr(p->str[0], '/'))
	{
		i = 0;
		while (path[i])
		{
			join = ft_strjoin(path[i], "/");
			join = ft_strjoin(join, p->str[0]);
			if (access(join, R_OK) == 0)
				execve(join, p->str, k);
			i++;
		}
		cmd_not_found(p);
	}
	execve(p->str[0], p->str, k);
}

void	cmd_not_found(t_simple_cmd *p)
{
	ft_putstr_fd("sash: ", 2);
	ft_putstr_fd(p->str[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	one_cmd_nob(t_all *all, t_simple_cmd *p)
{
	int		i;
	char	**k;
	t_var	*key;

	i = fork();
	if (i == 0)
	{
		dup2(p->in_fd, 0);
		dup2(p->out_fd, 1);
		k = my_env(all);
		key = check_char(all->env, "PATH");
		if (key)
			check_path(key, k, p);
		execve(p->str[0], p->str, k);
		perror("");
	}
	else
		wait(&i);
}

void	one_cmd_nb(t_all *all, t_simple_cmd *p)
{
	int		i;
	char	**k;
	t_var	*key;

	k = my_env(all);
	key = check_char(all->env, "PATH");
	if (key)
		check_path(key, k, p);
	execve(p->str[0], p->str, k);
	perror("");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:49:15 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/18 08:07:18 by ysahih           ###   ########.fr       */
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

void	cmd_not_found(t_simple_cmd *p)
{
	ft_putstr_fd("sash: ", 2);
	ft_putstr_fd(p->str[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
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

static	int	ft_count(int n)
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


int	my_atoi(char *str)
{
	int	i;
	int	s;
	int	n;

	s = 1;
	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(s *= -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - 48;
		i++;
	}
	return (n * s);
}

void	sigreset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	one_cmd_nob(t_all *all, t_simple_cmd *p)
{
	int		i;
	char	**k;
	char	*str;
	int		new;
	t_var	*key;
	t_var	*shelvl_ex;
	t_var	*shelvl_en;

	i = fork();
	if (i == 0)
	{
		sigreset();
		if (!ft_strcmp(p->str[0], "./sash"))
		{
			shelvl_en = check_char(all->env, "SHLVL");
			shelvl_ex = check_char(all->exp, "SHLVL");
			dup2(p->in_fd, 0);
			dup2(p->out_fd, 1);
			new = my_atoi(shelvl_en->val);
			new++;
			free (shelvl_en->val);
			free (shelvl_ex->val);
			str = ft_itoa(new);
			shelvl_en->val = NULL;
			shelvl_en->val = ft_strdup(str);
			shelvl_ex->val = NULL;
			shelvl_ex->val = ft_strdup(str);
			// return ;
		}
		k = my_env(all);
		if (p->err)
		{
			ft_putstr_fd("sash : ", 2);
			ft_putstr_fd(strerror(p->err), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		dup2(p->in_fd, 0);
		dup2(p->out_fd, 1);
		key = check_char(all->env, "PATH");
		if (key)
			check_path(key, k, p);
		execve(p->str[0], p->str, k);
		perror("");
	}
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:27:46 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/24 17:48:10 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_env(t_all *all)
{
	char	path[800];

	add_exen_back(&all->exp, lstnew_exen(ft_strdup("OLDPWD"), NULL));
	add_exen_back(&all->exp, lstnew_exen(ft_strdup("PWD"), \
	ft_strdup(getcwd(path, 800))));
	add_exen_back(&all->exp, lstnew_exen(ft_strdup("SHLVL"), \
	ft_strdup("1")));
	add_exen_back(&all->env, lstnew_exen(ft_strdup("PWD"), \
	ft_strdup(getcwd(path, 800))));
	add_exen_back(&all->env, lstnew_exen(ft_strdup("SHLVL"), \
	ft_strdup("1")));
	add_exen_back(&all->env, lstnew_exen(ft_strdup("_"), \
	ft_strdup("/usr/bin/env")));
}

void	set_env(t_all *all, char **env)
{
	int		i;
	char	**str;

	i = 0;
	all->env = NULL;
	all->exp = NULL;
	if (!*env)
	{
		empty_env(all);
		return ;
	}
	while (env[i])
	{
		str = ft_split(env[i]);
		lst_var(&all->env, str);
		lst_var(&all->exp, str);
		ft_freee(str);
		i++;
	}
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

char	**ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	if (p)
		free(p);
	return (NULL);
}

void	free_enex(t_var *lst)
{
	t_var		*p;
	t_var		*p1;

	p = lst;
	while (p)
	{
		p1 = p->next;
		if (p->key)
			free(p->key);
		p->key = NULL;
		if (p->val)
			free(p->val);
		p->val = NULL;
		if (p)
			free (p);
		p = NULL;
		p = p1;
	}
}

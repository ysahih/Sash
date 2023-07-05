/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/01 18:39:57 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_all *all, t_simple_cmd *tmp)
{
	if (!tmp->next)
	{
		if (!ft_strcmp(tmp->str[0], "env"))
			env(all);
		else if (!ft_strcmp(tmp->str[0], "export"))
			export(all);
		else if (!ft_strcmp(tmp->str[0], "pwd"))
			pwd(all);
		else if (!ft_strcmp(tmp->str[0], "echo"))
			echo(tmp);
		else if (!ft_strcmp(tmp->str[0] , "unset"))
			unset(tmp, &all->env, &all->exp);
		else if (!ft_strcmp(tmp->str[0], "exit"))
			ex_it (all);
		else if (!ft_strcmp(tmp->str[0], "cd"))
			cd (all);
		else
			one_cmd_nb(all, tmp);
	}
}

void	many_cmds(t_all	*all, t_simple_cmd	*tmp)
{
	int i;
	int f;
	int fd[2];

	while (tmp)
	{
		if(tmp->next)
			pipe(fd);
		if (!ft_strcmp(tmp->str[0], "cd") ||  !ft_strcmp(tmp->str[0], "exit") || !ft_strcmp(tmp->str[0], "pwd") || !ft_strcmp(tmp->str[0], "env")\
		|| !ft_strcmp(tmp->str[0], "unset") || !ft_strcmp(tmp->str[0], "export") || !ft_strcmp(tmp->str[0], "echo"))
		{
			f = fork();
			if (f == 0)
			{
				one_cmd(all, tmp);
				exit (0);
			}
			else
				wait(&i);
		}
		else 
		{
			puts("aaa");
			if (!tmp->next)
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			}
			one_cmd_nb(all, tmp);
		}
		if (tmp->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		else
			close(0);
		tmp = tmp->next;
	}
}

int	exec(t_all *all)
{
	int i;
	t_simple_cmd *tmp;
	
	i = 0;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
		return (0);
	if (!tmp->next)
		one_cmd(all, tmp);
	else
		many_cmds(all, tmp);
	return (0);
}

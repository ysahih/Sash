/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/18 08:57:03 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_all *all, t_simple_cmd *tmp)
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
		ex_it(all);
	else if (!ft_strcmp(tmp->str[0], "cd"))
		cd (all);
	else
		one_cmd_nob(all, tmp);
}

int	is_builting(t_simple_cmd *tmp)
{
	if (!ft_strcmp(tmp->str[0], "cd") \
	|| !ft_strcmp(tmp->str[0], "exit") \
	|| !ft_strcmp(tmp->str[0], "pwd") \
	|| !ft_strcmp(tmp->str[0], "env") \
	|| !ft_strcmp(tmp->str[0], "unset") \
	|| !ft_strcmp(tmp->str[0], "export") \
	|| !ft_strcmp(tmp->str[0], "echo"))
		return (1);
	return (0);
}

void	many_cmds(t_all *all, t_simple_cmd *tmp)
{
	int				i;
	int				f;
	int				fd[2];
	int				f_d;
	t_simple_cmd	*t;

	t = tmp;
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		i = fork();
		if (i == 0)
		{
			dup2(f_d, 0);
			close(f_d);
			if (tmp->next) {
				dup2(fd[1], tmp->out_fd);
				close(fd[0]);
				close(fd[1]);
			}
			if (is_builting(tmp))
				one_cmd(all, tmp);
			else
				one_cmd_nb(all, tmp);
		}
		else
		{
			if (tmp->next) {
				dup2(fd[0], f_d);
				close(fd[0]);
				close(fd[1]);
			} else {
				dup2(0, f_d);
			}
		}
		tmp = tmp->next;
	}
	while (t)
	{
		// if (!is_builting(t))
		wait(&f);
		t = t->next;
	}
}

int	exec(t_all *all)
{
	int				i;
	int				fd;
	t_simple_cmd	*tmp;

	i = 0;
	gl.rl = 1;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
	{
		if (tmp->err)
		{	
			ft_putstr_fd("sash : ", 2);
			ft_putstr_fd(strerror(tmp->err), 2);
			ft_putstr_fd("\n", 2);
		}
		return (0);
	}
	if (!tmp->next)
		one_cmd(all, tmp);
	else
		many_cmds(all, tmp);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/24 18:29:43 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	one_cmd(t_all *all, t_simple_cmd *tmp)
{
	if (!ft_strcmp(tmp->str[0], "env"))
		return (env(all), 0);
	else if (!ft_strcmp(tmp->str[0], "export"))
		return (export(all, tmp));
	else if (!ft_strcmp(tmp->str[0], "pwd"))
		return (pwd(all), 0);
	else if (!ft_strcmp(tmp->str[0], "echo"))
		return (echo(tmp), 0);
	else if (!ft_strcmp(tmp->str[0], "unset"))
		return (unset(tmp, &all->env, &all->exp));
	else if (!ft_strcmp(tmp->str[0], "exit"))
		return (ex_it(all));
	else if (!ft_strcmp(tmp->str[0], "cd"))
		return (cd (all));
	else
		one_cmd_nob(all, tmp);
	return (g_gl.exit_status);
}

void	in_child(t_all *all, t_simple_cmd *tmp, int fd[2])
{
	sigreset();
	if (tmp->out_fd != 1)
		dup2(tmp->out_fd, 1);
	if (tmp->in_fd >= 0)
		dup2(tmp->in_fd, 0);
	if (tmp->next)
	{
		if (tmp->out_fd == 1)
			dup2(fd[1], 1);
		else
			dup2(fd[1], tmp->out_fd);
		close(fd[0]);
		close(fd[1]);
	}
	if (is_builtin(tmp))
	{
		g_gl.exit_status = one_cmd(all, tmp);
		exit(g_gl.exit_status);
	}
	else
		one_cmd_nopipe(all, tmp);
}

void	closee(t_simple_cmd *tmp, int fd[2])
{
	if (tmp->next)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else
		close(0);
}

void	many_cmds(t_all *all, t_simple_cmd *tmp)
{
	int				i;
	int				fd[2];
	t_simple_cmd	*t;

	t = tmp;
	while (tmp)
	{
		tmp = empty_cmd(tmp);
		if (!tmp)
			return ;
		if (tmp->next)
			pipe(fd);
		i = fork();
		if (i == 0)
			in_child(all, tmp, fd);
		closee(tmp, fd);
		tmp = tmp->next;
	}
	tmp = t;
	while (t)
	{
		wa_itt(tmp, t);
		t = t->next;
	}
}

int	exec(t_all *all)
{
	int				i;
	int				fd;
	t_simple_cmd	*tmp;

	i = 0;
	g_gl.rl = 1;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	fd = dup(0);
	tmp = empty_cmd(tmp);
	if (!tmp)
		return (0);
	if (!tmp->next)
		g_gl.exit_status = one_cmd(all, tmp);
	else
		many_cmds(all, tmp);
	dup2(fd, 0);
	return (0);
}

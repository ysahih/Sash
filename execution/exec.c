/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/23 17:05:13 by ysahih           ###   ########.fr       */
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
	return (gl.exit_status);
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

void	wa_itt(t_simple_cmd *tmp, t_simple_cmd *t)
{
	int	status;

	if (wait(&status) == -1)
		exit(EXIT_FAILURE);
	if (WIFSIGNALED(status))
	{
		if (t == tmp)
		{
			if (WTERMSIG(status) == SIGINT)
			{
				write(1, "\n", 1);
				gl.exit_status = 130;
			}
			else if (WTERMSIG(status) == SIGQUIT)
			{
				write(1, "Quit: 3\n", 8);
				gl.exit_status = 131;
			}
		}
	}
	else if (WIFEXITED(status))
		gl.exit_status = WEXITSTATUS(status);
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
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (is_builting(tmp))
	{
		gl.exit_status = one_cmd(all, tmp);
		exit(gl.exit_status);
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

void	print_message(t_simple_cmd *tmp)
{
	if (tmp->err)
	{	
		ft_putstr_fd("sash : ", 2);
		ft_putstr_fd(strerror(tmp->err), 2);
		ft_putstr_fd("\n", 2);
	}
}

int	exec(t_all *all)
{
	int				i;
	t_simple_cmd	*tmp;

	i = 0;
	gl.rl = 1;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
		print_message(tmp);
	if (!tmp->next)
		gl.exit_status = one_cmd(all, tmp);
	else
		many_cmds(all, tmp);
	return (0);
}

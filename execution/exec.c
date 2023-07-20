/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/20 18:39:33 by kaboussi         ###   ########.fr       */
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
	int				status;
	int				fd[2];
	t_simple_cmd	*t;

	t = tmp;
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		i = fork();
		if (i == 0)
		{
			sigreset();
			if (tmp->out_fd != 1)
				dup2(tmp->out_fd, 1);
			if (tmp->in_fd != 0)
				dup2(tmp->in_fd, 0);
			if (tmp->next) {
				dup2(fd[1], tmp->out_fd);
				close(fd[0]);
				close(fd[1]);
			}
			if (is_builting(tmp))
			{
				// gl.exit_status = 
				// gl.exit_status = 
				one_cmd(all, tmp);
				exit(gl.exit_status);
			}
			else
				one_cmd_nopipe(all, tmp);
		}
		else
		{
			if (tmp->next) {
				dup2(fd[0], tmp->in_fd);
				close(fd[0]);
				close(fd[1]);
			} else {
				dup2(0, tmp->in_fd);
				close(0);
			}
		}
		tmp = tmp->next;
	}
	tmp = t;
	while (t)
	{
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
	fd = dup(0);
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
	dup2(fd, 0);
	return (0);
}

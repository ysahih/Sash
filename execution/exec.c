/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/06 19:57:45 by kaboussi         ###   ########.fr       */
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
		ex_it (all);
	else if (!ft_strcmp(tmp->str[0], "cd"))
		cd (all);
	else
		one_cmd_nob(all, tmp);
}

void    many_cmds(t_all    *all, t_simple_cmd    *tmp)
{
    int i;
    int f;
    int fd[2];
	int	f_d;

	t_simple_cmd *t = tmp;
    while (tmp)
    {
        if(tmp->next)
            pipe(fd);
        i = fork();
        if (i == 0)
        {
			dup2(f_d, 0);
            if (tmp->next)
            {
				if (tmp->out_fd == 1)
                	dup2(fd[1], 1);
				else
					dup2(tmp->out_fd, 1);
				
            }
			if (tmp->in_fd == 0)
            	dup2(fd[0], 0);
			else
				dup2(tmp->in_fd, 0);
            close(fd[1]);
            close(fd[0]);
            if (!ft_strcmp(tmp->str[0], "cd") ||  !ft_strcmp(tmp->str[0], "exit") || !ft_strcmp(tmp->str[0], "pwd") || !ft_strcmp(tmp->str[0], "env")\
            || !ft_strcmp(tmp->str[0], "unset") || !ft_strcmp(tmp->str[0], "export") || !ft_strcmp(tmp->str[0], "echo"))
                one_cmd(all, tmp);
            else 
            {
                one_cmd_nb(all, tmp);
            }
            if (tmp->next)
            {
				
                // dup2(fd[0], 0);
                close(fd[1]);
                close(fd[0]);
            }
            else {
                close(0);
				// dup(fd[0]);
				close(fd[0]);
				close(fd[1]);
			}
        }
        else
        {
            // wait(&f);
            // dup2(fd[0], 0);
            close(fd[1]);
			f_d = fd[0];
			if (tmp && !tmp->next)
            	close(fd[0]);
        }
        tmp = tmp->next;
    }
	while (t)
	{
		// int f;
          if (!(!ft_strcmp(t->str[0], "cd") ||  !ft_strcmp(t->str[0], "exit") || !ft_strcmp(t->str[0], "pwd") || !ft_strcmp(t->str[0], "env")\
            || !ft_strcmp(t->str[0], "unset") || !ft_strcmp(t->str[0], "export") || !ft_strcmp(t->str[0], "echo"))) {
				wait(&f);
			}
		t = t->next;
	}
}

int	exec(t_all *all)
{
	int i;
	int	fd;
	t_simple_cmd *tmp;
	
	i = 0;
	fd = dup(0);
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
		return (0);
	if (!tmp->next)
		one_cmd(all, tmp);
	else
		many_cmds(all, tmp);
	dup2(fd, 0);
	return (0);
}

    // wait(&f);llainaal zok mok
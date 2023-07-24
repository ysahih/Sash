/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:37:48 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/24 18:29:43 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_simple_cmd *tmp)
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

void	print_message(t_simple_cmd *tmp)
{
	if (tmp->err)
	{	
		ft_putstr_fd("sash : ", 2);
		ft_putstr_fd(strerror(tmp->err), 2);
		ft_putstr_fd("\n", 2);
	}
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
				g_gl.exit_status = 130;
			}
			else if (WTERMSIG(status) == SIGQUIT)
			{
				write(1, "Quit: 3\n", 8);
				g_gl.exit_status = 131;
			}
		}
	}
	else if (WIFEXITED(status))
		g_gl.exit_status = WEXITSTATUS(status);
}

t_simple_cmd	*empty_cmd(t_simple_cmd *tmp)
{
	if (!*(tmp->str))
	{
		print_message(tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	print_message_err(t_simple_cmd *tmp)
{
	if (tmp->err)
	{	
		ft_putstr_fd("sash : ", 2);
		ft_putstr_fd(strerror(tmp->err), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

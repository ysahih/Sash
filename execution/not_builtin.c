/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:49:15 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/24 13:18:07 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigreset(void)
{
	signal(SIGQUIT, SIG_ERR);
}

void	wa_it(void)
{
	int	status;

	if (wait(&status) == -1)
		exit(EXIT_FAILURE);
	if (WIFSIGNALED(status))
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
	else if (WIFEXITED(status))
		gl.exit_status = WEXITSTATUS(status);
}

void	notbuiltin_error(t_simple_cmd *p, int len, int flag)
{
	if (p->err && flag == 0)
	{
		ft_putstr_fd("sash : ", 2);
		ft_putstr_fd(strerror(p->err), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (flag == 1
		&& (p->str[0][0] == '/' || p->str[0][len - 1] == '/'))
	{
		ft_putstr_fd("sash: ", 2);
		ft_putstr_fd(p->str[0], 2);
		ft_putstr_fd(": ", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("sash: ", 2);
		ft_putstr_fd(p->str[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	one_cmd_nob(t_all *all, t_simple_cmd *p)
{
	int		i;
	char	**k;
	t_var	*key;
	int		len;

	i = fork();
	if (i == 0)
	{
		sigreset();
		shelvl(all, p);
		len = ft_strlen(p->str[0]);
		notbuiltin_error(p, len, 0);
		k = my_env(all);
		dup2(p->in_fd, 0);
		dup2(p->out_fd, 1);
		key = check_char(all->env, "PATH");
		if (key)
			check_path(key, k, p);
		else
			notbuiltin_error(p, len, 2);
		notbuiltin_error(p, len, 1);
		perror("");
		exit(126);
	}
	wa_it();
}

void	one_cmd_nopipe(t_all *all, t_simple_cmd *p)
{
	char	**k;
	t_var	*key;

	k = my_env(all);
	key = check_char(all->env, "PATH");
	if (key)
		check_path(key, k, p);
	execve(p->str[0], p->str, k);
	ft_freee(k);
	perror("");
}
